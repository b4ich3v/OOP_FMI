#include "Admin.h"
#include <algorithm>
#include <iostream>

MyVector<Admin::UserPtr> Admin::allUsers;

Admin::Admin(int id, const MyString& firstName,
    const MyString& lastName, const MyString& password)
    : User(firstName, lastName, password, Type::ADMIN)
{

    setId(id);
    allUsers.push_back(UserPtr(this));

}

Admin::UserPtr Admin::createUser(int id, const MyString& firstName, 
    const MyString& lastName, const MyString& password)
{

    User* raw = new User(firstName, lastName, password, Type::NONE);
    raw->setId(id);
    UserPtr userPtr(raw);
    allUsers.push_back(userPtr);

    return userPtr;

}

void Admin::deleteUser(int userId)
{

    bool removed = false;

    for (int i = 0; i < allUsers.size(); i++)
    {

        if (allUsers[i]->getId() == userId) 
        {
            
            for (int j = i; j + 1 < allUsers.size(); j++)
            {

                allUsers[j] = allUsers[j + 1];

            }

            allUsers.pop_back();
            removed = true;
            break;

        }

    }

    if (!removed) std::cout << "Error" << std::endl;

}

void Admin::broadcast(const MyString& content, const DateTime& date)
{

    for (int i = 0; i < allUsers.size(); i++)
    {

        User* currentRecipient = allUsers[i].get();

        if (currentRecipient->getId() == getId()) continue;

        Message currentMessage(this, currentRecipient, content, date);
        sendMessage(currentMessage);

    }

}

void Admin::viewInboxAll() const
{

    for (int i = 0; i < allUsers.size(); i++)
    {

        const UserPtr& currentUserPtr = allUsers[i];
        const MyVector<Message>& inbox = currentUserPtr->getInboxHistory();
        std::cout << "Inbox for user ID " << currentUserPtr->getId() << ":" << std::endl;

        for (int j = 0; j < inbox.size(); j++)
        {

            const Message& currentMessage = inbox[j];
            std::cout << toString(currentMessage) << std::endl;

        }

    }

}

MyString Admin::toString(const Message& message) 
{

    MyString result = message.getDate().toString();
    result = result + " from ID ";
    
    std::string idStr = std::to_string(message.getSender()->getId());
    result = result + MyString(idStr.c_str());
    result = result + ": ";
    result = result + message.getContent();

    return result;

}

const MyVector<Admin::UserPtr>& Admin::getAllUsers() 
{

    return allUsers;

}
