#include <iostream>
#include <cstring>
#include <fstream>

namespace HELPERS
{

	const char OPENING_SYMBOL = '>';
	const char CLOSING_SYMBOL = '<';

	const int MAX_SIZE_SHIPS = 30;
	const int MAX_FILE_SIZE = 128;
	const int MAX_BUFFER_SIZE = 1024;

	const char OPENING_TABLE[8] = "<table>";
	const char OPENING_TH[5] = "<th>";
	const char OPENING_TR[5] = "<tr>";
	const char OPENING_TD[5] = "<td>";

	const char CLOSING_TABLE[9] = "</table>";
	const char CLOSING_TH[6] = "</th>";
	const char CLOSING_TR[6] = "</tr>";
	const char CLOSING_TD[6] = "</td>";

	const char ONE_TAB[2] = "	";
	const char TWO_TABS[3] = "		";

}

enum class ClassOfShip
{

	battleship = 0,
	battlecruiser = 1

};

class Ship
{
private:

	char* name = nullptr;
	int yearOfLaunch = 1900;
	ClassOfShip classOfShip = ClassOfShip::battlecruiser;
	int countOfGuns = 0;

	void setName(const char* name)
	{

		if (!name) return;

		delete[] this->name;

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	void setCountOfGuns(int countOfGuns)
	{

		if (countOfGuns < 0) return;

		this->countOfGuns = countOfGuns;

	}

	void setYearOfLaunch(int yearOfLaunch)
	{

		if (yearOfLaunch < 0) return;

		this->yearOfLaunch = yearOfLaunch;

	}

	void setClassofShip(ClassOfShip classOfShip)
	{

		this->classOfShip = classOfShip;

	}

	void free()
	{

		delete[] name;
		name = nullptr;

		countOfGuns = 0;
		yearOfLaunch = 0;
		classOfShip = ClassOfShip::battleship;

	}

	void copyFrom(const Ship& other)
	{

		name = new char[strlen(other.name) + 1];
		strncpy(name, other.name, strlen(other.name));
		name[strlen(other.name)] = '\0';

		yearOfLaunch = other.yearOfLaunch;
		countOfGuns = other.countOfGuns;
		classOfShip = other.classOfShip;

	}

public:

	Ship() = default;

	Ship(const char* name, int countOfGuns, int yearOfLaunch, ClassOfShip classOfShip)
	{

		setName(name);
		setCountOfGuns(countOfGuns);
		setYearOfLaunch(yearOfLaunch);
		setClassofShip(classOfShip);

	}

	Ship(const Ship& other)
	{

		copyFrom(other);

	}

	Ship& operator = (const Ship& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Ship()
	{

		free();

	}

	const char* getName() const
	{

		return name;

	}

	int getYearOfLaunch() const
	{

		return yearOfLaunch;

	}

	int getCountOfGuns() const
	{

		return countOfGuns;

	}

	ClassOfShip getClassOfShip() const
	{

		return classOfShip;

	}

	void printShip() const
	{

		std::cout << name << " ";
		std::cout << yearOfLaunch << " ";
		std::cout << countOfGuns << " ";

		switch (classOfShip)
		{

		case ClassOfShip::battleship: std::cout << "battleship"; break;
		case ClassOfShip::battlecruiser: std::cout << "battlecruiser"; break;
		default: break;

		}

		std::cout << std::endl;

	}

};

class Navy
{
private:

	char* countryName = nullptr;
	Ship ships[HELPERS::MAX_SIZE_SHIPS];
	int countOfShips = 0;

	void copyFrom(const Navy& other)
	{

		if (other.countryName)
		{

			countryName = new char[strlen(other.countryName) + 1];
			strncpy(countryName, other.countryName, strlen(other.countryName));
			countryName[strlen(other.countryName)] = '\0';

		}
		else countryName = nullptr;

		countOfShips = other.countOfShips;

		for (int i = 0; i < countOfShips; i++)
		{

			ships[i] = other.ships[i];

		}

	}

	void free()
	{

		delete[] countryName;
		countryName = nullptr;
		countOfShips = 0;

	}

	void setCountryName(const char* name)
	{

		delete[] countryName;

		if (!name)
		{

			countryName = new char[1];
			countryName[0] = '\0';

		}
		else
		{

			countryName = new char[strlen(name) + 1];
			strcpy(countryName, name);

		}

	}

public:

	Navy()
	{

		countryName = new char[1];
		countryName[0] = '\0';
		countOfShips = 0;

	}

	Navy(const Navy& other)
	{

		copyFrom(other);

	}

	Navy(const char* name)
	{

		setCountryName(name);

	}

	Navy& operator = (const Navy& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Navy()
	{

		free();

	}

	void addShip(const Ship& ship)
	{

		if (countOfShips == HELPERS::MAX_SIZE_SHIPS) return;

		ships[countOfShips] = ship;
		countOfShips += 1;

	}

	void removeShip(const char* name)
	{

		for (int i = 0; i < countOfShips; i++)
		{

			if (!strcmp(ships[i].getName(), name))
			{

				std::swap(ships[i], ships[countOfShips - 1]);
				countOfShips -= 1;
				break;

			}

		}

	}

	const Ship* const getShipPtrByIndex(int index)
	{

		if (index < 0 || index >= countOfShips) return nullptr;

		Ship* ptrShip = &ships[index];
		return ptrShip;

	}

	int getCountOfShips() const
	{

		return countOfShips;

	}

	int getTotalCountOfGuns() const
	{

		int result = 0;

		for (int i = 0; i < countOfShips; i++)
		{

			result += ships[i].getCountOfGuns();

		}

		return result;

	}

	int compareByCountOfGuns(const Navy& other) const
	{

		if (getTotalCountOfGuns() < other.getTotalCountOfGuns()) return -1;
		else if (getTotalCountOfGuns() > other.getTotalCountOfGuns()) return 1;
		else return 0;

	}

	void printNavy() const
	{

		for (int i = 0; i < countOfShips; i++)
		{

			ships[i].printShip();

		}

		std::cout << std::endl;

	}

	const Ship& getShipByIndex(int index) const
	{

		return ships[index];

	}

	const char* getName() const
	{

		return countryName;

	}

};

class NavyHtmlTableGenerator
{
private:

	char fileName[HELPERS::MAX_FILE_SIZE + 1];
	Navy* navy = nullptr;

	void setFileName(const char* fileName)
	{

		if (!fileName) return;

		strncpy(this->fileName, fileName, strlen(fileName));
		this->fileName[strlen(fileName)] = '\0';

	}

	void setNavy(Navy* navy)
	{

		this->navy = navy;

	}

	void writeShipName(std::ofstream& file, const char* name) const
	{

		file << HELPERS::TWO_TABS << HELPERS::OPENING_TD;
		file << name;
		file << HELPERS::TWO_TABS << HELPERS::CLOSING_TD;
		file << std::endl;

	}

	void writeYearOfLaunch(std::ofstream& file, int yearOfLaunch) const
	{

		file << HELPERS::TWO_TABS << HELPERS::OPENING_TD;
		file << yearOfLaunch;
		file << HELPERS::TWO_TABS << HELPERS::CLOSING_TD;
		file << std::endl;

	}

	void writeClassOfShip(std::ofstream& file, ClassOfShip classOfShip) const
	{

		file << HELPERS::TWO_TABS << HELPERS::OPENING_TD;

		if ((int)classOfShip == (int)ClassOfShip::battlecruiser) file << "Battlecruiser";
		else file << "Battleship";

		file << HELPERS::TWO_TABS << HELPERS::CLOSING_TD;
		file << std::endl;

	}

	void writeCountOfGuns(std::ofstream& file, int countOfGuns) const
	{

		file << HELPERS::TWO_TABS << HELPERS::OPENING_TD;
		file << countOfGuns;
		file << HELPERS::TWO_TABS << HELPERS::CLOSING_TD;
		file << std::endl;

	}

	void writeShipInFile(std::ofstream& file, const Navy& navy, int index) const
	{

		Ship currentShip = navy.getShipByIndex(index);

		file << HELPERS::ONE_TAB << HELPERS::OPENING_TR;
		file << std::endl;

		writeShipName(file, currentShip.getName());
		writeYearOfLaunch(file, currentShip.getYearOfLaunch());
		writeClassOfShip(file, currentShip.getClassOfShip());
		writeCountOfGuns(file, currentShip.getCountOfGuns());

		file << HELPERS::ONE_TAB << HELPERS::CLOSING_TR;
		file << std::endl;

	}

	void writeNavyNameInFile(std::ofstream& file, const char* name) const
	{

		file << HELPERS::ONE_TAB << HELPERS::OPENING_TR;
		file << std::endl;

		file << HELPERS::TWO_TABS << HELPERS::OPENING_TH;
		file << name;
		file << HELPERS::TWO_TABS << HELPERS::CLOSING_TH;
		file << std::endl;

	}

	void writeNavyCountOfShipsFile(std::ofstream& file, int countOfShips) const
	{

		file << HELPERS::TWO_TABS << HELPERS::OPENING_TH;
		file << countOfShips;
		file << HELPERS::TWO_TABS << HELPERS::CLOSING_TH;
		file << std::endl;

		file << HELPERS::ONE_TAB << HELPERS::CLOSING_TR;
		file << std::endl;

	}

	void writeNavyDataInFile(std::ofstream& file, const Navy& navy) const
	{

		writeNavyNameInFile(file, navy.getName());
		writeNavyCountOfShipsFile(file, navy.getCountOfShips());

	}

	void trim(char* string) const
	{

		int i = 0;

		while (string[i] != '\0' && (string[i] == ' ' || string[i] == '\t')) i++;

		if (i > 0)
		{

			int j = 0;

			while (string[i] != '\0')
			{

				string[j++] = string[i++];

			}

			string[j] = '\0';

		}

		int size = 0;

		while (string[size] != '\0') size++;

		if (size > 0)
		{

			int k = size - 1;

			while (k >= 0 && (string[k] == ' ' || string[k] == '\t'))
			{

				string[k] = '\0';
				k--;

			}

		}

	}

	void processLine(char* currentLine, int bufferSize) const
	{

		char* position1 = nullptr;

		for (int i = 0; currentLine[i] != '\0'; i++)
		{

			if (currentLine[i] == HELPERS::OPENING_SYMBOL)
			{

				position1 = &currentLine[i];
				break;

			}

		}

		char* position2 = nullptr;

		for (int i = 0; currentLine[i] != '\0'; i++)
		{

			if (currentLine[i] == HELPERS::CLOSING_SYMBOL)
			{

				position2 = &currentLine[i];

			}

		}

		if (position1 != nullptr && position2 != nullptr && position2 > position1)
		{

			int prefixLen = position1 - currentLine + 1;
			char prefix[HELPERS::MAX_BUFFER_SIZE];

			for (int i = 0; i < prefixLen; i++) prefix[i] = currentLine[i];
			prefix[prefixLen] = '\0';

			char suffix[HELPERS::MAX_BUFFER_SIZE];
			int s = 0;

			for (int i = position2 - currentLine; currentLine[i] != '\0'; i++) suffix[s++] = currentLine[i];
			suffix[s] = '\0';

			int innerLen = position2 - position1 - 1;
			char inner[HELPERS::MAX_BUFFER_SIZE];

			for (int i = 0; i < innerLen; i++) inner[i] = position1[1 + i];
			inner[innerLen] = '\0';

			trim(inner);

			char newLine[HELPERS::MAX_BUFFER_SIZE];
			int k = 0;

			for (int i = 0; prefix[i] != '\0'; i++) newLine[k++] = prefix[i];

			for (int i = 0; inner[i] != '\0'; i++) newLine[k++] = inner[i];

			for (int i = 0; suffix[i] != '\0'; i++) newLine[k++] = suffix[i];

			newLine[k] = '\0';

			int i = 0;

			while (i < (int)bufferSize - 1 && newLine[i] != '\0')
			{

				currentLine[i] = newLine[i];
				i++;

			}

			currentLine[i] = '\0';

		}

	}

public:

	NavyHtmlTableGenerator(const char* fileName, Navy* navy)
	{

		setFileName(fileName);
		setNavy(navy);

	}

	void saveToHtmlTable() const
	{

		const char* tempFileName = "temp.txt";
		std::ofstream fileTemp(tempFileName);
		if (!fileTemp.is_open()) return;

		fileTemp << HELPERS::OPENING_TABLE;
		fileTemp << std::endl;

		writeNavyDataInFile(fileTemp, *navy);

		for (int i = 0; i < (*navy).getCountOfShips(); i++)
		{

			writeShipInFile(fileTemp, *navy, i);

		}

		fileTemp << HELPERS::CLOSING_TABLE;
		fileTemp.close();

		std::ifstream in(tempFileName);
		if (!in.is_open()) return;

		std::ofstream out(fileName);
		if (!out.is_open()) return;

		char line[HELPERS::MAX_BUFFER_SIZE];

		while (in.getline(line, HELPERS::MAX_BUFFER_SIZE))
		{

			processLine(line, HELPERS::MAX_BUFFER_SIZE);
			out << line;
			out << std::endl;

		}

		in.close();
		out.close();
		remove(tempFileName);

	}

};

int main()
{

	Ship ship1("Black Pearl", 30, 341, ClassOfShip::battleship);
	Ship ship2("Silent death", 38, 1891, ClassOfShip::battleship);
	Ship ship3("Vin Dieasel", 0, 2014, ClassOfShip::battlecruiser);

	Ship ship4("Yoan Baychev", 30, 341, ClassOfShip::battleship);
	Ship ship5("Ivo Kunchev", 38, 1891, ClassOfShip::battleship);
	Ship ship6("Ilian Zaprqnov", 576, 201, ClassOfShip::battleship);
	Ship ship7("Kaloyan Markov", 891, 14, ClassOfShip::battlecruiser);
	Ship ship8("Tugay Kafa", 131, 786, ClassOfShip::battleship);

	Navy navy1("The machines");
	navy1.addShip(ship1);
	navy1.addShip(ship2);
	navy1.addShip(ship3);

	Navy* ptr = &navy1;

	NavyHtmlTableGenerator html("../result.txt", ptr);
	html.saveToHtmlTable();

	return 0;

}
