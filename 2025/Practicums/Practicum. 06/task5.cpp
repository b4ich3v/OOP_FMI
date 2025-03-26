#include <iostream>
#include <cstring>

namespace HELPERS
{

	const int MAX_SIZE_BUFFER = 1024;
	const int MAX_OPENED_WEBPAGES = 30;

}

class Webpage
{
private:

	char* address = nullptr;
	char* ipAddress = nullptr;

	void free()
	{

		delete[] address;
		delete[] ipAddress;

		address = nullptr;
		ipAddress = nullptr;

	}

	void copyFrom(const Webpage& other) 
	{

		address = new char[strlen(other.address) + 1];
		ipAddress = new char[strlen(other.ipAddress) + 1];

		strncpy(address, other.address, strlen(other.address));
		strncpy(ipAddress, other.ipAddress, strlen(other.ipAddress));

		address[strlen(other.address)] = '\0';
		ipAddress[strlen(other.ipAddress)] = '\0';

	}

public:

	Webpage() = default;

	Webpage(const char* address, const char* ipAddress) 
	{

		this->address = new char[strlen(address) + 1];
		this->ipAddress = new char[strlen(ipAddress) + 1];

		strncpy(this->address, address, strlen(address));
		strncpy(this->ipAddress, ipAddress, strlen(ipAddress));

		this->address[strlen(address)] = '\0';
		this->ipAddress[strlen(ipAddress)] = '\0';

	}

	Webpage(const Webpage& other)
	{

		copyFrom(other);

	}

	Webpage& operator = (const Webpage& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Webpage()
	{

		free();

	}

	friend std::ostream& operator << (std::ostream& os, const Webpage& web) 
	{

		int size1 = strlen(web.address);
		int size2 = strlen(web.ipAddress);

		os << size1 << " " << web.address << std::endl;
		os << size2 << " " << web.ipAddress << std::endl;

		return os;

	}

	friend std::istream& operator >> (std::istream& is, Webpage& web)
	{

		web.free();

		int size1 = 0;
		int size2 = 0;

		char buffer[HELPERS::MAX_SIZE_BUFFER];

		is >> size1 >> buffer;
		web.address = new char[size1 + 1];
		strncpy(web.address, buffer, size1);
		web.address[size1] = '\0';

		is >> size2 >> buffer;
		web.ipAddress = new char[size2 + 1];
		strncpy(web.ipAddress, buffer, size2);
		web.ipAddress[size2] = '\0';

		return is;

	}
	
	const char* getAddress() const 
	{

		return address;

	}

	const char* getIpAdddress() const
	{

		return ipAddress;

	}

};

class Browser 
{
private:

	Webpage pages[HELPERS::MAX_OPENED_WEBPAGES];
	int countOfOpenedWebs = 0;

public:

	Browser() = default;

	Browser(const Browser& other) 
	{

		this->countOfOpenedWebs = other.countOfOpenedWebs;

		for (int i = 0; i < countOfOpenedWebs; i++)
		{

			pages[i] = other.pages[i];

		}

	}

	void addPage(const Webpage& page) 
	{

		if (countOfOpenedWebs == HELPERS::MAX_OPENED_WEBPAGES) return;

		pages[countOfOpenedWebs] = page;
		countOfOpenedWebs += 1;

	}

	void removePage(const Webpage& page)
	{

		for (int i = 0; i < countOfOpenedWebs; i++)
		{

			if (!strcmp(pages[i].getAddress(), page.getAddress()) &&
				!strcmp(pages[i].getIpAdddress(), page.getIpAdddress()))
			{

				std::swap(pages[i], pages[countOfOpenedWebs - 1]);
				countOfOpenedWebs -= 1;
				break;

			}

		}

	}

	Browser& operator += (const Webpage& page) 
	{

		addPage(page);

	}

	Browser& operator -= (int index)
	{

		if (index < 0 || index >= countOfOpenedWebs) throw std::logic_error("Error");

		Webpage pageToBeRemoved(pages[index]);
		removePage(pageToBeRemoved);

	}

	void printPages() const
	{

		for (int i = 0; i < countOfOpenedWebs; i++)
		{

			std::cout << pages[i];

		}

		std::cout << std::endl;

	}

};

int main()
{

	Webpage page1; // 26, https://github.com/b4ich3v, 11, 51.41.11.81
	Webpage page2; // 30, https://github.com/ivayloknchv, 11, 52.42.12.82
	Webpage page3("https://github.com/KristianIvanov24", "52.43.12.8");

	std::cin >> page1;
	std::cin >> page2;
	std::cout << std::endl;

	Browser browser;
	browser.addPage(page1);
	browser.addPage(page2);
	browser.addPage(page3);
	browser.printPages();

	Browser browserCopy(browser);
	browserCopy -= 1;
	browserCopy.printPages();

	return 0;

}
