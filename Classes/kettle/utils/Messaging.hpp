//
//  Messaging.hpp
//  Plazma Lights Off
//
//  Created by Derek Higgs on 6/2/16.
//  Copyright © 2016 Derek Higgs. All rights reserved.
//

#ifndef Messaging_hpp
#define Messaging_hpp

#include "StringHash.hpp"

namespace kettle {
namespace utils {
    class UserInfo;
    
    /**
     * Interface for objects that send messages.
     */
    class ISender {
    public:
        /**
         * Deconstructor.
         */
        virtual ~ISender() {}
        
        /**
         * Gets the type of the sender for downcasting.
         */
        virtual hash_t getType() const = 0;
        
    protected:
        /**
         * Constructor.
         */
        ISender() {}
        
    private:
        // disable copy and assign
        ISender(const ISender &);
        void operator=(const ISender &);
    }; // class ISender
    
    /**
     * Bundles together data to make a message.
     */
    struct Message {
        /**
         * The message code.
         */
        hash_t code;
        
        /**
         * The sender of the message. May be null.
         */
        const ISender * sender;
        
        /**
         * Extra data for the message. May be null.
         */
        const UserInfo * user_info;
    }; // struct Message
    
    /**
     * An interface for receiving messages.
     */
    class IMessageReceiver {
    public:
        /**
         * Deconstructor.
         */
        virtual ~IMessageReceiver() {}
        
        /**
         * Receives a message.
         */
        virtual void receive(const Message & message) const = 0;
        
    protected:
        /**
         * Constructor.
         */
        IMessageReceiver() {}
        
    private:
        // disable copy and assign
        IMessageReceiver(const IMessageReceiver &);
        void operator=(const IMessageReceiver &);
    }; // class IMessageReceiver
    
    /**
     * Value to specify that any message can be received.
     */
    const hash_t kMessageCodeAny = hashCString("any message");
    
    /**
     * A messaging system.
     */
    class Messaging {
    public:
        /**
         * Constructor.
         */
        Messaging();
        
        /**
         * Deconstructor.
         */
        ~Messaging();
        
        /**
         * Adds a message reciever.
         *
         * @param message_receiver  The receiver to get messages.
         * @param code              The message code the receiver can obtain.
         *                          Set to kMessageCodeAny to receive all
         *                          message codes.
         * @param sender            The sender the receiver can obtain. Set to
         *                          null to receive from any sender.
         * @return                  This instance.
         */
        Messaging & addMessageReceiver(IMessageReceiver * message_receiver,
                                       hash_t code = kMessageCodeAny,
                                       const ISender * sender = nullptr);
        
        /**
         * Removes a message reciever.
         *
         * @param message_receiver  The receiver to get messages.
         * @param code              The message code that was registered.
         * @param sender            The sender that was registered.
         * @return                  This instance.
         */
        Messaging & removeMessageReceiver(IMessageReceiver * message_receiver,
                                          hash_t code = kMessageCodeAny,
                                          const ISender * sender = nullptr);
        
        /**
         * Removes a message reciever from receiving any messages.
         *
         * @param message_receiver  The receiver to get messages.
         * @return                  This instance.
         */
        Messaging & removeMessageReceiver(IMessageReceiver * message_receiver);
        
        /**
         * Send a message.
         *
         * @param code          The message code.
         * @param sender        The sender of the message.
         * @param user_info     Extra info of the message.
         * @return              This instance.
         */
        void post(hash_t code,
                  const ISender * sender = nullptr,
                  const UserInfo * user_info = nullptr) const;
        
        /**
         * Send a message.
         *
         * @param message   The message.
         * @return          This instance.
         */
        void post(const Message & message) const;
        
    protected:
        /**
         * The private implementation.
         */
        struct PrivateImplementation;
        PrivateImplementation * m_private_implementation;
        
    private:
        // disable copy and assign
        Messaging(const Messaging &);
        void operator=(const Messaging &);
    }; // class Messaging
} // namespace utils
} // namespace kettle

#endif /* Messaging_hpp */
