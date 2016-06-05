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
    
    class ISender {
    public:
        virtual ~ISender() {}
        
        virtual StringHash getType() const = 0;
        
    protected:
        ISender() {}
        
    private:
        // disable copy and assign
        ISender(const ISender &);
        void operator=(const ISender &);
    }; // class ISender
    
    struct Message {
        const StringHash code;
        const ISender * const sender;
        const UserInfo * const user_info;
    }; // struct Message
    
    class IMessageReceiver {
    public:
        virtual ~IMessageReceiver() {}
        
        virtual void receive(const Message * message) const = 0;
        
    protected:
        IMessageReceiver() {}
        
    private:
        // disable copy and assign
        IMessageReceiver(const IMessageReceiver &);
        void operator=(const IMessageReceiver &);
    }; // class IMessageReceiver
    
    const StringHash kMessageCodeAny("any message");
    
    class Messaging {
    public:
        Messaging();
        ~Messaging();
        
        void addMessageReceiver(IMessageReceiver * message_receiver,
                                StringHash code = kMessageCodeAny,
                                const ISender * sender = nullptr);
        
        void post(StringHash code,
                  const ISender * sender = nullptr,
                  const UserInfo * user_info = nullptr);
        
        void post(const Message & message);
        
    protected:
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
