#include "MyVector.hpp"
#include "Message.h"
#include "IAuthenticatable.h"
#pragma once

class IMessageCarrier: public IAuthenticatable
{
public:

    virtual void sendMessage(const Message& message) = 0;

    virtual MyVector<Message> receiveMessages() = 0;

    virtual ~IMessageCarrier() = default;

};


