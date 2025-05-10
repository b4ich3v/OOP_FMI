#include "IMessageCarrier.h"
#pragma once

enum class Type
{

    NONE = -1,
    TEACHER = 0,
    STUDENT = 1,
    ADMIN = 2

};

class User: public IMessageCarrier 
{
private:

    Type type;
    MyString firstName; 
    MyString lastName; 
    MyString password;

    int id = 0;
    static int maskId;
    bool isLogged = false;

    MyVector<Message> inbox;    
    MyVector<Message> outbox;

public:
    
    User(const MyString& firstName, const MyString& lastName, 
        const MyString& password, Type type);

    int getId() const override;

    void setId(int newId) override;

    bool login(const MyString& password) override;

    void logout() override;

    bool changePassword(const MyString& oldPassword, const MyString& newPassword) override;

    void sendMessage(const Message& message) override;

    MyVector<Message> receiveMessages() override;

    const MyVector<Message>& getInboxHistory() const;

    const MyVector<Message>& getOutboxHistory() const;

    Type getType() const;

    const MyString& getFirstName() const;

    const MyString& getLastName() const;

    const MyString& getPassword() const;

};


