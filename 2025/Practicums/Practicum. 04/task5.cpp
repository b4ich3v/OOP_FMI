#include <iostream>
#include <fstream>
#include <cstdint>
#include <cstring>

namespace CONSTANTS
{

	const int MAX_NAME_SIZE = 32;
	const int DEFAULT_MASK = 0b0;
	const char SEPARATOR = '|';
	const int MAX_COUNT_PROGRAMMERS = 50;
	const int NEW_SALARY_USER = 200;

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

	Programmer()
	{

		setName("Default name");
		setAge(18);
		setSalary(2500);
		setLanguage(Language::ASEMBLY);

	}

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

	Language getLanguage() const
	{

		return lan;

	}

	int getSalary() const
	{
	
		return salary;

	}
	
	int getAge() const 
	{

		return age;

	}

	const char* getName() const
	{
		
		return name;

	}

};

typedef int (*predicate1)(int);
typedef bool (*predicate2)(const Programmer&, const Programmer&);

class SoftwareCompany
{
private:

	Programmer prs[CONSTANTS::MAX_COUNT_PROGRAMMERS];
	int countOfProgrammers;
	
	static bool bySalary(const Programmer& p1, const Programmer& p2)
	{

		return p1.getSalary() > p2.getSalary();

	}

	static bool byAge(const Programmer& p1, const Programmer& p2) 
	{

		return p1.getAge() > p2.getAge();

	}

	void sort(predicate2 func)
	{

		for (int i = 0; i < countOfProgrammers - 1; i++)
		{

			for (int j = 0; j < countOfProgrammers - i - 1; j++)
			{

				if (func(prs[j], prs[j + 1]))
				{

					std::swap(prs[j], prs[j + 1]);

				}

			}

		}

	}

public:

	SoftwareCompany()
	{

		countOfProgrammers = 0;

	}

	void addProgrammer(const Programmer& pr) 
	{

		if (countOfProgrammers == CONSTANTS::MAX_COUNT_PROGRAMMERS) return;

		prs[countOfProgrammers] = pr;
		countOfProgrammers += 1;

	}

	int getCounOfProgrammers() const
	{

		return countOfProgrammers;
		
	}

	void printAllProgrammers() const 
	{

		for (int i = 0; i < countOfProgrammers; i++)
		{

			prs[i].printProgrammer();

		}

	}

	void printStudentByLanguage(Language lan)
	{

		for (int i = 0; i < countOfProgrammers; i++)
		{

			if ((int)prs[i].getLanguage() == (int)lan)
			{

				prs[i].printProgrammer();

			}

		}

	}

	double getAvarageSalary() const
	{

		double sum = 0;

		for (int i = 0; i < countOfProgrammers; i++)
		{

			sum += prs[i].getSalary();

		}

		return sum / countOfProgrammers;

	}

	double getAvarageAge() const
	{

		double sum = 0;

		for (int i = 0; i < countOfProgrammers; i++)
		{

			sum += prs[i].getAge();

		}

		return sum / countOfProgrammers;

	}

	void changeSalaryToProgrammer(const Programmer& pr, predicate1 func) 
	{

		for (int i = 0; i < countOfProgrammers; i++)
		{

			if (!strcmp(pr.getName(), prs[i].getName()))
			{

				prs[i].setSalary(func(CONSTANTS::NEW_SALARY_USER));

			}

		}

	}

	void sortBySalary() 
	{

		sort(bySalary);

	}

	void sortByAge()
	{

		sort(byAge);

	}

};

int main()
{

	Programmer pr1("Yoan Baychev", 20, 4999, Language::C);
	Programmer pr2("Koki Markov", 21, 3879, Language::CPP);
	Programmer pr3("Ivo Kunchev", 21, 2501, Language::ASEMBLY);
	Programmer pr4("Ilian Zaprqnov", 46, 0, Language::HTML);

	uint8_t newMask = ((int)Language::CPP | (int)Language::JAVA | (int)Language::PYTHON);
	pr1.setLanguage(newMask);
	pr1.printProgrammer();

	SoftwareCompany company;
	company.addProgrammer(pr1);
	company.addProgrammer(pr2);
	company.addProgrammer(pr3);
	company.addProgrammer(pr4);

	company.printAllProgrammers();
	std::cout << std::endl;
	company.sortByAge();

	company.printAllProgrammers();
	std::cout << std::endl;
	company.sortByAge();
	
	company.printAllProgrammers();


	return 0;

}
