#include <iostream>
#include <fstream>
#include "MyString.h"

class Timestamp
{
private:

	unsigned long long seconds = 0;

public:

	Timestamp() = default;

	Timestamp(int seconds): seconds(seconds) {}

	void setSeconds(int seconds) 
	{

		this->seconds = seconds;

	}

	int getSeconds() const 
	{

		return seconds;

	}

};

class TimestampWithDescription : public Timestamp
{
private:

	char* data = nullptr;

	void free() 
	{
		
		delete[] data;
		data = nullptr;

	}

	void copyFrom(const TimestampWithDescription& other) 
	{

		this->data = new char[strlen(other.data) + 1];
		strncpy(this->data, other.data, strlen(other.data));
		this->data[strlen(other.data)] = '\0';

	}

	void moveTo(TimestampWithDescription&& other) 
	{

		this->data = data;
		setSeconds(other.getSeconds());

		other.data = nullptr;
		other.setSeconds(0);

	}

public:

	TimestampWithDescription() = default;

	TimestampWithDescription(const char* data, unsigned long long seconds) : Timestamp(seconds)
	{

		this->data = new char[strlen(data) + 1];
		strncpy(this->data, data, strlen(data));
		this->data[strlen(data)] = '\0';

	}

	TimestampWithDescription(const TimestampWithDescription& other): Timestamp(other.getSeconds())
	{

		copyFrom(other);

	}

	TimestampWithDescription& operator = (const TimestampWithDescription& other) 
	{

		if (this != &other) 
		{

			setSeconds(other.getSeconds());
			free();
			copyFrom(other);

		}

		return *this;

	}

	TimestampWithDescription& operator = (TimestampWithDescription&& other) noexcept 
	{

		if (this != &other)
		{

			setSeconds(other.getSeconds());
			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	TimestampWithDescription& operator += (unsigned long long number)
	{

		setSeconds(getSeconds() + number);

	}

	TimestampWithDescription(TimestampWithDescription&& other) noexcept: Timestamp(other.getSeconds())
	{

		moveTo(std::move(other));

	}

	~TimestampWithDescription() 
	{

		free();

	}

	void print() const 
	{

		std::cout << data << std::endl;
		std::cout << getSeconds() << std::endl;

	}

	void setTheSeconds(int seconds) 
	{

		setSeconds(seconds);

	}

	const char* getData() const 
	{

		return data;

	}

	int getTheSeconds() const 
	{

		return getSeconds();

	}

	friend std::ostream& operator << (std::ostream& os, const TimestampWithDescription& other) 
	{

		os << other.getData();
		os << " " << other.getTheSeconds();

		return os;

	}

	friend std::istream& operator >> (std::istream& is, TimestampWithDescription& other)
	{

		char buffer[1024];
		int seconds = 0;

		is.getline(buffer, 1024);
		is >> seconds;

		other.free();
		other.setTheSeconds(seconds);
		other.data = new char[strlen(buffer) + 1];
		strncpy(other.data, buffer, strlen(buffer));
		other.data[strlen(buffer)] = '\0';

		return is;

	}

};

int main()
{

	TimestampWithDescription twd1("I like pigs", 187317481);
	twd1.print();

	std::cout << twd1.getData() << std::endl;
	std::cout << twd1.getTheSeconds() << std::endl;

	TimestampWithDescription twd2;
	std::cin >> twd2;
	std::cout << twd2 << std::endl;

	twd2 += 1486;
	std::cout << twd2 << std::endl;

	return 0;

}

