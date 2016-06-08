//
//  Messaging.cpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/2/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#include "Messaging.hpp"

#include <map>
#include <set>
#include <vector>

namespace kettle {
namespace utils {
    /**
     * A list of message receivers.
     */
    typedef std::vector<IMessageReceiver *> MessageReceiverVector;
    
    /**
     * The message receivers grouped by the message code.
     */
    typedef std::map<StringHash, MessageReceiverVector> MessageReceiversByCode;
    
    /**
     * The message receivers grouped by the sender.
     */
    typedef std::map<const ISender *, MessageReceiversByCode> MessageReceiversBySender;
    
namespace {
    /**
     * Removed the message receiver.
     *
     * @param message_receivers     The set of message receivers.
     * @param code                  The message code that was registered.
     * @param sender                The sender that was registered.
     * @param iter                  The iterator pointing to the message
     *                              receiver to erase.
     */
    void erase(MessageReceiversBySender & message_receivers,
               const ISender * sender,
               const StringHash & code,
               MessageReceiverVector::iterator & iter) {
        message_receivers[ sender ][ code ].erase(iter);
        if(message_receivers.size() == 0) {
            message_receivers[ sender ].erase( code );
            if(message_receivers[ sender ].size() == 0) {
                message_receivers.erase( sender );
            }
        }
    }
    
    /**
     * Inserts all of the message receivers into the set.
     *
     * @param set               The set to fill.
     * @param message_receiver  The receivers to insert.
     */
    void insertAllIntoSet(std::set<IMessageReceiver *> & set,
                          const MessageReceiverVector & message_receiver) {
        set.insert(message_receiver.begin(), message_receiver.end());
    }
} // namespace
    
    struct Messaging::PrivateImplementation {
        MessageReceiversBySender message_receivers;
    }; // struct Messaging::PrivateImplementation
    
    Messaging::Messaging() :
            m_private_implementation(new PrivateImplementation) {}
    
    Messaging::~Messaging() {
        delete m_private_implementation;
    }
    
    void Messaging::addMessageReceiver(IMessageReceiver * message_receiver,
                                       StringHash code,
                                       const ISender * sender) {
        m_private_implementation->message_receivers[ sender ][ code ].push_back(message_receiver);
    }
    
    void Messaging::removeMessageReceiver(IMessageReceiver * message_receiver,
                                          StringHash code,
                                          const ISender * sender) {
        MessageReceiverVector & message_receivers =
                m_private_implementation->message_receivers[ sender ][ code ];
        for(std::vector<IMessageReceiver *>::iterator iter = message_receivers.begin();
            iter != message_receivers.end();
            ++iter) {
            
            if(*iter == message_receiver) {
                erase(m_private_implementation->message_receivers,
                      sender,
                      code,
                      iter);
            }
        }
    }
    
    void Messaging::removeMessageReceiver(IMessageReceiver * message_receiver) {
        for(MessageReceiversBySender::iterator by_sender_iter =
                    m_private_implementation->message_receivers.begin(),
            by_sender_end = m_private_implementation->message_receivers.end();
            by_sender_iter != by_sender_end;
            ++by_sender_iter) {
            
            for(MessageReceiversByCode::iterator by_code_iter =
                        by_sender_iter->second.begin(),
                by_code_end = by_sender_iter->second.end();
                by_code_iter != by_code_end;
                ++by_code_iter) {
                
                for(MessageReceiverVector::iterator receiver_iter =
                            by_code_iter->second.begin(),
                    receiver_end = by_code_iter->second.end();
                    receiver_iter != receiver_end;
                    ++receiver_iter) {
                    
                    if(*receiver_iter == message_receiver) {
                        erase(m_private_implementation->message_receivers,
                              by_sender_iter->first,
                              by_code_iter->first,
                              receiver_iter);
                    }
                }
            }
        }
    }
    
    void Messaging::post(StringHash code,
                         const ISender * sender,
                         const UserInfo * user_info) const {
        Message message = { code, sender, user_info };
        post(message);
    }
    
    void Messaging::post(const Message & message) const {
        MessageReceiversBySender & all_message_receivers =
        m_private_implementation->message_receivers;
        const ISender * sender = message.sender;
        const StringHash & code = message.code;
        
        std::set<IMessageReceiver *> message_receivers;
        insertAllIntoSet(message_receivers,
                         all_message_receivers[ sender ][ code ]);
        
        // Post to the receivers of any message code.
        insertAllIntoSet(message_receivers,
                         all_message_receivers[ sender ][ kMessageCodeAny ]);
        
        // Post to the receivers for any senders.
        insertAllIntoSet(message_receivers,
                         all_message_receivers[ nullptr ][ code ]);
        
        // Post to the receivers for any message.
        insertAllIntoSet(message_receivers,
                         all_message_receivers[ nullptr ][ kMessageCodeAny ]);
        
        for(std::set<IMessageReceiver *>::iterator iter = message_receivers.begin();
            iter != message_receivers.end();
            ++iter) {
            
            (**iter).receive(message);
        }
    }
} // namespace utils
} // namespace kettle