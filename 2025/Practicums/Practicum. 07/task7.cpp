#include <iostream>
#include <cstring>

enum class EyeColor
{

	BLUE = 0,
	GREEN = 1,
	BROWN = 2,
	BLACK = 3

};

class Lady
{
private:

	char* name = nullptr;
	int age = 0;
	int countOfRoses = 0;
	int bachelorId = 0;

	void free() 
	{

		delete[] name;
		name = nullptr;

		age = 0;
		countOfRoses = 0;
		bachelorId = 0;

	}

	void copyFrom(const Lady& other) 
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));
		this->name[strlen(other.name)] = '\0';

		this->age = other.age;
		this->countOfRoses = other.countOfRoses;
		this->bachelorId = other.bachelorId;

	}

public:

	Lady() = default;

	Lady(const Lady& other) 
	{

		copyFrom(other);

	}

	Lady(const char* name, int age, int bachelorId)
	{

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		this->age = age;
		this->countOfRoses = 0;
		this->bachelorId = bachelorId;

	}

	Lady& operator = (const Lady& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Lady() 
	{

		free();

	}

	bool receiveRose(int id)
	{

		if (bachelorId != id) return false;

		countOfRoses += 1;
		return true;

	}

	int getCountOfRoses() const 
	{

		return countOfRoses;

	}

	void printLady() const 
	{

		std::cout << name << " ";
		std::cout << age << " ";
		std::cout << countOfRoses << std::endl;

	}

};

class Bachelor
{
private:

	char* name = nullptr;
	int age = 0;
	char* profession = nullptr;
	char* phrase = nullptr;
	EyeColor colorOfEyes = EyeColor::BLACK;

	int currentId = 0;
	static int idMask;

	void copyFrom(const Bachelor& other)
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));
		this->name[strlen(other.name)] = '\0';

		this->profession = new char[strlen(other.profession) + 1];
		strncpy(this->profession, other.profession, strlen(other.profession));
		this->profession[strlen(other.profession)] = '\0';

		this->phrase = new char[strlen(other.phrase) + 1];
		strncpy(this->phrase, other.phrase, strlen(other.phrase));
		this->phrase[strlen(other.phrase)] = '\0';

		this->colorOfEyes = other.colorOfEyes;
		this->age = other.age;
		this->currentId = other.currentId;

	}

	void free()
	{

		delete[] name;
		name = nullptr;

		delete[] profession;
		profession = nullptr;

		delete[] phrase;
		phrase = nullptr;

		colorOfEyes = EyeColor::BLACK;
		age = 0;
		currentId = 0;

	}

public:

	Bachelor(): name(nullptr), profession(nullptr), phrase(nullptr), colorOfEyes(EyeColor::BROWN), age(0)
	{

		currentId = idMask;
		idMask += 1;

	}

	Bachelor(const Bachelor& other)
	{

		copyFrom(other);

	}

	Bachelor(const char* name, int age, const char* profession, const char* phrase, EyeColor colorOfEyes)
	{

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		this->profession = new char[strlen(profession) + 1];
		strncpy(this->profession, profession, strlen(profession));
		this->profession[strlen(profession)] = '\0';

		this->phrase = new char[strlen(phrase) + 1];
		strncpy(this->phrase, phrase, strlen(phrase));
		this->phrase[strlen(phrase)] = '\0';

		this->colorOfEyes = colorOfEyes;
		this->age = age;
		this->currentId = idMask;
		idMask += 1;

	}

	Bachelor& operator = (const Bachelor& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Bachelor()
	{

		free();

	}

	void giveRoseTo(Lady& lady) const
	{

		lady.receiveRose(currentId);

	}

	void printBachelor() const
	{

		std::cout << name << " ";
		std::cout << age << " ";
		std::cout << profession << " ";
		std::cout << phrase << " ";
		std::cout << (int)colorOfEyes << " ";
		std::cout << currentId << std::endl;

	}

	int getId() const 
	{

		return currentId;

	}

};

int Bachelor::idMask = 0;

class BachelorHouse 
{
private:

	Bachelor* men = nullptr;
	int countOfMen = 0;
	int capacityForMen = 8;

	Lady* women = nullptr;
	int countOfWomen = 0;
	int capacityForWomen = 8;

	void free() 
	{

		delete[] men;
		men = nullptr;

		delete[] women;
		women = nullptr;

		countOfMen = 0;
		countOfWomen = 0;

		capacityForMen = 8;
		capacityForWomen = 8;

	}

	void resizeForMen(int newCapacity) 
	{

		if (newCapacity <= capacityForMen) return;

		Bachelor* newMen = new Bachelor[newCapacity];

		for (int i = 0; i < countOfMen; i++)
		{

			newMen[i] = men[i];

		}

		delete[] men;
		men = newMen;
		capacityForMen = newCapacity;

	}

	void resizeForWomen(int newCapacity)
	{

		if (newCapacity <= capacityForWomen) return;

		Lady* newWomen = new Lady[newCapacity];

		for (int i = 0; i < countOfWomen; i++)
		{

			newWomen[i] = women[i];

		}

		delete[] women;
		women = newWomen;
		capacityForWomen = newCapacity;

	}

public:

	BachelorHouse()
	{

		this->countOfMen = 0;
		this->countOfWomen = 0;

		this->capacityForMen = 1;
		this->capacityForWomen = 3;

		this->men = new Bachelor[capacityForMen];
		this->women = new Lady[capacityForWomen];

	}

	BachelorHouse(const BachelorHouse& other) = delete;

	BachelorHouse& operator = (const BachelorHouse& other) = delete;

	~BachelorHouse()
	{

		free();

	}

	void addBachelor(const Bachelor& bachelor) 
	{

		if (countOfMen == capacityForMen) resizeForMen(capacityForMen * 2);

		men[countOfMen] = bachelor;
		countOfMen += 1;

	}

	void addLady(const Lady& lady)
	{

		if (countOfWomen == capacityForWomen) resizeForWomen(capacityForWomen * 2);

		women[countOfWomen] = lady;
		countOfWomen += 1;

	}

	void removeLadyAt(int index) 
	{

		for (int i = index; i < countOfWomen - 1; i++)
		{

			women[i] = women[i + 1];

		}

		countOfWomen -= 1;

	}

	void printAll() const 
	{

		for (int i = 0; i < countOfMen; i++)
		{

			men[i].printBachelor();

		}

		std::cout << std::endl;

		for (int i = 0; i < countOfWomen; i++)
		{

			women[i].printLady();

		}

		std::cout << std::endl;

	}

	void simulateShow()
	{

		int counterMask = 0;
		int counterForRounds = 0;

		while (countOfWomen > countOfMen) 
		{

			std::cout << "Round number: " << counterForRounds + 1 << std::endl;
			counterForRounds += 1;

			for (int i = 0; i < countOfMen; i++)
			{

				counterMask += 1;
				men[i].giveRoseTo(women[countOfWomen % counterMask]);

			}

			std::cout << "Eliminated women are: " << std::endl;

			for (int i = 0; i < countOfWomen; i++)
			{

				if (women[i].getCountOfRoses() == 0) 
				{

					women[i].printLady();
					removeLadyAt(i);

				}

			}

			std::cout << std::endl;

		}

	}

};

int main()
{

	Bachelor b1("Yoan Baychev", 20, "AI engineer", "All in", EyeColor::BLUE);
	Bachelor b2("Ivailo Kunchev", 20, "Professor", "I love maths", EyeColor::BROWN);
	Bachelor b3("Ilian Zaprqnov", 21, "Data engineer", "The bigger, the better", EyeColor::BLACK);
	Bachelor b4("Kaloyan Markov", 21, "Content creator", "So what?", EyeColor::GREEN);

	Lady l1("Lady 1", 28, 0);
	Lady l2("Lady 2", 21, 1);
	Lady l3("Lady 3", 25, 2);
	Lady l4("Lady 3", 31, 1);
	Lady l5("Lady 5", 22, 0);
	Lady l6("Lady 6", 19, 0);
	Lady l7("Lady 7", 22, 3);
	Lady l8("Lady 8", 19, 3);
	Lady l9("Lady 9", 29, 0);
	Lady l10("Lady 10", 20, 2);

	BachelorHouse house;
	house.addBachelor(b1);
	house.addBachelor(b2);
	house.addBachelor(b3);
	house.addBachelor(b4);

	house.addLady(l1);
	house.addLady(l2);
	house.addLady(l3);
	house.addLady(l4);
	house.addLady(l5);
	house.addLady(l6);
	house.addLady(l7);
	house.addLady(l8);
	house.addLady(l9);
	house.addLady(l10);

	house.printAll();
	house.simulateShow();

	return 0;

}
