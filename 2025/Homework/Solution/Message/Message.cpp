#include "Message.h"

Message::Message():
	sender(nullptr), recipient(nullptr),
	content(""), date() {}

Message::Message(User* sender, User* recipient,
	const MyString& content, const DateTime& date):
	sender(sender), recipient(recipient), 
	content(content), date(date) {}

DateTime Message::getDate() const 
{

	return date;

}

MyString Message::getContent() const
{

	return content;

}

User* Message::getSender() const
{

	return sender;

}

User* Message::getRecipient() const
{

	return recipient;

}
