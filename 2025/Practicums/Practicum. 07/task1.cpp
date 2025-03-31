#include <iostream>
#include <cstring>

namespace HELPERS 
{

	const int MAX_SIZE_NAME = 18;
	const int MAX_SIZE_PHONE = 10;
	const int MAX_SIZE_BOOKS = 50;

}

class User
{
private:

	char name[HELPERS::MAX_SIZE_NAME + 1];
	char phoneNumber[HELPERS::MAX_SIZE_PHONE + 1];

public:

	User(const char* name, const char* phoneNumber)
	{

		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		strncpy(this->phoneNumber, phoneNumber, strlen(phoneNumber));
		this->phoneNumber[strlen(phoneNumber)] = '\0';

	}

	void printUser() const
	{

		std::cout << name << " ";
		std::cout << phoneNumber << " ";
		std::cout << std::endl;

	}

};

class Book 
{
private:

	const User* currentUser = nullptr;

	static int idMask;
	int id = 0;

	char* authorName = nullptr;
	char* title = nullptr;
	bool status = false;

	void copyFrom(const Book& other)
	{

		authorName = new char[strlen(other.authorName) + 1];
		strncpy(authorName, other.authorName, strlen(other.authorName));
		authorName[strlen(other.authorName)] = '\0';

		title = new char[strlen(other.title) + 1];
		strncpy(title, other.title, strlen(other.title));
		title[strlen(other.title)] = '\0';

		status = other.status;
		id = other.id;
		currentUser = other.currentUser;

	}

	void free() 
	{

		delete[] authorName;
		delete[] title;

		authorName = nullptr;
		title = nullptr;
		status = false;
		currentUser = nullptr;

	}

	void setStatus()
	{

		status = !status;

	}

public:

	Book() : title(nullptr), authorName(nullptr), status(false)
	{

		currentUser = nullptr;
		id += 1;

	}

	Book(const Book& other)
	{

		copyFrom(other);

	}

	Book(const char* authorName, const char* title)
	{

		this->authorName = new char[strlen(authorName) + 1];
		strncpy(this->authorName, authorName, strlen(authorName));
		this->authorName[strlen(authorName)] = '\0';

		this->title = new char[strlen(title) + 1];
		strncpy(this->title, title, strlen(title));
		this->title[strlen(title)] = '\0';

		status = false;

		id = idMask;
		idMask += 1;
		currentUser = nullptr;

	}

	Book& operator = (const Book& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Book()
	{

		free();

	}

	int getId()
	{

		return id;

	}

	void getBook(const User& user)
	{

		currentUser = &user;
		setStatus();

	}

	void printBook() const 
	{

		std::cout << authorName << " ";
		std::cout << title << " ";
		std::cout << id << " ";
		std::cout << status << " ";
		if (currentUser != nullptr) (*currentUser).printUser();
		else std::cout << "No current user" << std::endl;

	}

	void setUser(const User& user) 
	{

		currentUser = &user;
		setStatus();

	}

};

int Book::idMask = 0;

class Library
{
private:

	Book books[HELPERS::MAX_SIZE_BOOKS];
	int countOfBooks = 0;

public:

	Library() = default;

	void addBook(const Book& book)
	{

		if (countOfBooks == HELPERS::MAX_SIZE_BOOKS) throw std::logic_error("Error");

		books[countOfBooks] = book;
		countOfBooks += 1;

	}

	void getBookById(int id, const User& user) 
	{

		for (int i = 0; i < countOfBooks; i++)
		{

			if (books[i].getId() == id) 
			{

				books[i].setUser(user);
				return;

			}

		}

	}

	void printBooks() const
	{

		for (int i = 0; i < countOfBooks; i++)
		{

			books[i].printBook();

		}

	}

};

int main()
{

	User user1("Yoan Baychev", "0878663...");
	User user2("Ilian Zaprqnov", "0897645...");
	user1.printUser();
	user2.printUser();
	std::cout << std::endl;

	Book b1("Author1", "b1");
	Book b2("Author2", "b2");
	Book b3("Author3", "b3");
	Book b4("Author4", "b4");

	Library lib;
	lib.addBook(b1);
	lib.addBook(b2);
	lib.addBook(b3);
	lib.addBook(b4);
	lib.printBooks();

	std::cout << std::endl;

	lib.getBookById(3, user1);
	lib.getBookById(1, user2);
	lib.printBooks();

	return 0;

}
