#include "MyString.h"
#include "IEntity.h"
#pragma once

class IAuthenticatable: public IEntity
{
public:

    virtual bool login(const MyString& password) = 0;

    virtual void logout() = 0;

    virtual bool changePassword(const MyString& oldPassword, const MyString& newPassword) = 0;

    virtual ~IAuthenticatable() = default;

};
