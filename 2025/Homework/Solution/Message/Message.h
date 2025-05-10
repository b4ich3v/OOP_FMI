#include "MyString.h"
#include "DateTime.h"
#pragma once

class User;

class Message
{
private:

	User* sender = nullptr;
	User* recipient = nullptr;

	MyString content;
	DateTime date;

public:

	Message();

	Message(User* sender, User* recipient, 
		const MyString& content, const DateTime& date);

	DateTime getDate() const;

	MyString getContent() const;

	User* getSender() const;

	User* getRecipient() const;

};

