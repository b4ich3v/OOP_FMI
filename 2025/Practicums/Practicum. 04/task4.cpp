#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

namespace CONSTANTS
{

	const int MAX_NAME_SIZE = 32;
	const int DEFAULT_MASK = 0b0;
	const char SEPARATOR = '|';

}

enum class Language
{

	CPP = (1 << 0),
	JAVA = (1 << 1),
	JAVA_SCRIPT = (1 << 2),
	PYTHON = (1 << 3),
	C = (1 << 4),
	ASEMBLY = (1 << 5),
	HTML = (1 << 6),
	HASKSEL = (1 << 7)

};

class Programmer
{
private:

	uint8_t mask = CONSTANTS::DEFAULT_MASK;
	char name[CONSTANTS::MAX_NAME_SIZE + 1];
	int age;
	int salary;
	Language lan;

	void setAge(int age)
	{

		if (age < 18) return;

		this->age = age;

	}

	void setName(const char* name)
	{

		if (this->name == name || !strcmp(this->name, name) || !name) return;

		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	bool isUpperBit(uint8_t number, int index)
	{

		if (index < 0 || index >= 8) return false;

		return (number & (1 << index)) != 0;

	}

public:

	Programmer(const char* name, int age, int salary, Language lan)
	{

		setName(name);
		setAge(age);
		setSalary(salary);
		setLanguage(lan);

	}

	void setLanguage(Language lan)
	{

		this->lan = lan;
		mask |= (int)lan;

	}

	void setSalary(int salary)
	{

		if (salary < 2500 || salary > 5000) return;

		this->salary = salary;

	}

	void setLanguage(uint8_t newMask)
	{

		mask = newMask;

		for (int i = 0; i < 8; i++)
		{

			if (isUpperBit(mask, i))
			{

				setLanguage((Language)(1 << i));

			}

		}

	}

	void printProgrammer() const
	{


		std::cout << name << " " << CONSTANTS::SEPARATOR << " ";
		std::cout << age << " " << CONSTANTS::SEPARATOR << " ";
		std::cout << salary << " " << CONSTANTS::SEPARATOR << " ";

		std::cout << "{ ";

		switch (lan)
		{

		case Language::CPP: std::cout << "CPP ";
		case Language::JAVA: std::cout << "JAVA ";
		case Language::JAVA_SCRIPT: std::cout << "JAVA_SCRIPS ";
		case Language::PYTHON: std::cout << "PYTHON ";
		case Language::C: std::cout << "C ";
		case Language::ASEMBLY: std::cout << "ASEMBLY ";
		case Language::HTML: std::cout << "HTML ";
		case Language::HASKSEL: std::cout << "HASKEL ";
		default: break;

		}

		std::cout << "}" << std::endl;

	}

};

int main()
{

	Programmer pr1("Yoan Baychev", 20, 4999, Language::C);
	uint8_t newMask = ((int)Language::CPP | (int)Language::JAVA | (int)Language::PYTHON);
	pr1.setLanguage(newMask);
	pr1.printProgrammer();

	return 0;

}
