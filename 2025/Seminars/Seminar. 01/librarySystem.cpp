#include <iostream>

enum class Status : uint8_t
{

	Available,
	Borrowed,
	Reserved,
	None

};

struct Book
{
public:

	char* tittle;
	char* author;
	int publicationYear;
	Status status;

	void copyFrom(const Book& other)
	{

		tittle = new char[strlen(other.tittle) + 1];
		strncpy(tittle, other.tittle, strlen(other.tittle));

		author = new char[strlen(other.author) + 1];
		strncpy(author, other.author, strlen(other.author));

		publicationYear = other.publicationYear;

	}

	void moveTo(Book&& other)
	{

		tittle = other.tittle;
		author = other.author;
		publicationYear = other.publicationYear;

		other.tittle = nullptr;
		other.author = nullptr;
		other.publicationYear = 0;

	}

	void free()
	{

		delete[] tittle;
		delete[] author;
		tittle = nullptr;
		author = nullptr;
		publicationYear = 0;
		status = Status::None;


	}

	Book() : tittle(nullptr), author(nullptr), publicationYear(0)
	{

		status = Status::None;

	}

	Book(const char* tittle, const char* author, int publicationYear)
	{

		this->tittle = new char[strlen(tittle) + 1];
		strncpy(this->tittle, tittle, strlen(tittle));

		this->author = new char[strlen(author) + 1];
		strncpy(this->author, author, strlen(author));

		this->publicationYear = publicationYear;

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

	Book& operator = (Book&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	Book(const Book& other)
	{

		copyFrom(other);

	}

	Book(Book&& other) noexcept
	{

		moveTo(std::move(other));

	}

	~Book() 
	{

		free();

	}

	bool operator == (const Book& other) const
	{

		return !strcmp(tittle, other.tittle);

	}

};

struct Library
{
public:

	char* name;
	int bookCount;
	Book books[10];

	void copyFrom(const Library& other) 
	{

		name = new char[strlen(other.name) + 1];
		strncpy(name, other.name, strlen(other.name));

		bookCount = other.bookCount;

		for (int i = 0; i < bookCount; i++)
		{

			books[i] = other.books[i];

		}

	}

	void moveTo(Library&& other) 
	{

		name = other.name;

		bookCount = other.bookCount;

		for (int i = 0; i < bookCount; i++)
		{

			books[i] = other.books[i];

		}

		other.name = nullptr;
		other.bookCount = 0;

	}

	void free()
	{

		delete[] name;
		name = nullptr;
		bookCount = 0;

	}

	Library() : name(nullptr), bookCount(0) {}

	Library(const Library& other) 
	{

		copyFrom(other);

	}

	Library(Library&& other) noexcept
	{

		moveTo(std::move(other));

	}

	Library& operator = (const Library& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Library& operator = (Library&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Library()
	{

		free();

	}

	void addBook(const char* tittle, const char* author, int publicationYear)
	{

		if (bookCount == 10) return;

		for (int i = 0; i < bookCount; i++)
		{

			if (!strcmp(books[i].tittle, tittle) &&
				!strcmp(books[i].author, author) &&
				books[i].publicationYear == publicationYear)
			{

				return;

			}

		}

		Book newBook(tittle, author, publicationYear);
		books[bookCount] = newBook;
		bookCount += 1;

	}

	void borrowBook(Book& book)
	{

		for (int i = 0; i < bookCount; i++)
		{

			if (books[i] == book)
			{

				books[i].status = Status::Borrowed;
				break;

			}

		}

	}

	void reserveBook(Book& book)
	{

		for (int i = 0; i < bookCount; i++)
		{

			if (books[i] == book)
			{

				books[i].status = Status::Reserved;
				break;

			}

		}

	}

	void print(const Book& book) const
	{

		std::cout << book.tittle << " " << book.author << " " << book.publicationYear;

		switch (book.status)
		{
		case Status::Available: std::cout << "available"; break;
		case Status::Borrowed: std::cout << "borrowed"; break;
		case Status::Reserved: std::cout << "reserved"; break;
		default: break;

		}

	}

	void printLibrary() const
	{

		for (int i = 0; i < bookCount; i++)
		{

			print(books[i]);
			std::cout << std::endl;

		}

	}

};

