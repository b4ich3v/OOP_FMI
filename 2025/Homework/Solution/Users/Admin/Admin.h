#include "User.h"
#include "MyString.h"
#include "MySharedPtr.hpp"
#include <sstream>
#pragma once

class Admin: public User 
{
private:

    using UserPtr = MySharedPtr<User>;
    static MyVector<UserPtr> allUsers;

public:
    
    Admin(int id, const MyString& firstName,
        const MyString& lastName, const MyString& password);

    UserPtr createUser(int id, const MyString& firstName, 
        const MyString& lastName, const MyString& password);

    void deleteUser(int userId);

    void broadcast(const MyString& content, const DateTime& date);

    void viewInboxAll() const;

    static MyString toString(const Message& message);

    static const MyVector<UserPtr>& getAllUsers();

};
