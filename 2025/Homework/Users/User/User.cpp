#include "User.h"

int User::maskId = 0;

User::User(const MyString& firstName, const MyString& lastName,
	const MyString& password, Type type)
{

	if (!login(password)) throw std::logic_error("Error");

	this->id = maskId;
	this->firstName = firstName;
	this->lastName = lastName;
	this->password = password;
	this->type = type;

	maskId += 1;

}

int User::getId() const 
{

	return id;

}

void User::setId(int newId) 
{

	this->id = newId;

}

bool User::login(const MyString& password)
{

	bool pred = !strcmp(this->password.getData(), password.getData());
	
	if (pred) { isLogged = true; return true; }
	else { isLogged = false; return false; }

}

void User::logout()
{

	if (!isLogged) return;
	isLogged = false;
	// TODO

}

bool User::changePassword(const MyString& oldPassword,
	const MyString& newPassword)
{

	if (strcmp(oldPassword.getData(), newPassword.getData())) return false;
	password = newPassword;

	return true;

}

void User::sendMessage(const Message& message) 
{
	
	outbox.push_back(message);

	User* recipient = message.getRecipient();
	recipient->inbox.push_back(message);

}

MyVector<Message> User::receiveMessages() 
{
	
	return inbox;

}

const MyVector<Message>& User::getInboxHistory() const 
{

	return inbox;

}

const MyVector<Message>& User::getOutboxHistory() const 
{

	return outbox;

}

Type User::getType() const
{

	return type;

}

const MyString& User::getFirstName() const 
{

	return firstName;

}

const MyString& User::getLastName() const 
{

	return lastName;

}

const MyString& User::getPassword() const 
{

	return password;

}
