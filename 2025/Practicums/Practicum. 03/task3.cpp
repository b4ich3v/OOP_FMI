#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS
{

	const int NAME_MAX_SIZE = 50;
	const int COUNT_MAX_JEDIS = 100;
	const int MAX_BUFFER_SIZE = 1024;
	const int COUNT_OF_COLORS = 5;
	const int COUNT_OF_TYPES = 3;

	int getFileSize(std::ifstream& file)
	{

		int currentPos = file.tellg();
		file.seekg(0, std::ios::end);
		int result = file.tellg();
		file.seekg(currentPos);
		file.clear();

		return result;

	}

	int getCountOfJedisInTxt(std::ifstream& file)
	{

		char buffer[MAX_BUFFER_SIZE + 1];
		int counter = 0;

		while (true)
		{

			file.getline(buffer, MAX_BUFFER_SIZE);
			counter += 1;

			if (file.eof()) break;

		}

		file.clear();
		file.seekg(0, std::ios::beg);

		return counter - 1;

	}
}

enum class Color
{

	RED = 0,
	YELLOW = 1,
	GREEN = 2,
	BLUE = 3,
	PURPLE = 4

};

enum class Type
{

	SINGLEBLADED = 0,
	DOUBLE_BLADED = 1,
	CROSSGUARD = 2

};

struct LightSaber
{
public:

	Color color;
	Type type;

};

struct Jedi
{
public:

	char name[HELPERS::NAME_MAX_SIZE + 1];
	int age;
	int power;
	LightSaber saber;

};

struct JediCollection
{
public:

	Jedi jedis[HELPERS::COUNT_MAX_JEDIS];
	int countOfJedis;

};

Jedi createJedi(const char* name, unsigned age, unsigned power, const LightSaber& saber)
{

	if (!name) return { "Unknown", -1, -1, {Color::BLUE, Type::CROSSGUARD} };

	Jedi result;

	strncpy(result.name, name, strlen(name));
	result.name[strlen(name)] = '\0';
	result.age = age;
	result.power = power;
	result.saber = saber;

	return result;

}

Jedi createJedi(const char* name, unsigned age, unsigned power, Color color, Type type)
{

	createJedi(name, age, power, { color,type });

}

void addJedi(JediCollection& collection, const Jedi& jedi)
{

	if (collection.countOfJedis == HELPERS::COUNT_MAX_JEDIS) return;

	collection.jedis[collection.countOfJedis] = jedi;
	collection.countOfJedis += 1;

}

void removeJedi(JediCollection& collection, const char* name)
{

	if (!name) return;

	for (int i = 0; i < collection.countOfJedis; i++)
	{

		if (!strcmp(collection.jedis[i].name, name))
		{

			std::swap(collection.jedis[i], collection.jedis[collection.countOfJedis - 1]);
			collection.countOfJedis -= 1;
			break;

		}

	}

}

void printSaber(LightSaber saber)
{

	switch (saber.color)
	{

	case Color::BLUE: std::cout << "BLUE "; break;
	case Color::RED: std::cout << "RED "; break;
	case Color::GREEN: std::cout << "GREEN "; break;
	case Color::YELLOW: std::cout << "YELLOW "; break;
	case Color::PURPLE: std::cout << "PURPLE "; break;
	default: break;

	}

	switch (saber.type)
	{

	case Type::SINGLEBLADED: std::cout << "SINGLEBLADED "; break;
	case Type::DOUBLE_BLADED: std::cout << "DOUBLE_BLADED "; break;
	case Type::CROSSGUARD: std::cout << "CROSSGUARD "; break;
	default: break;

	}

}

void printJedi(const Jedi& jedi)
{

	std::cout << jedi.name << " " << jedi.age << " " << jedi.power << " ";
	printSaber(jedi.saber);
	std::cout << std::endl;

}

void printJediCollection(const JediCollection& collection)
{

	for (int i = 0; i < collection.countOfJedis; i++)
	{

		printJedi(collection.jedis[i]);

	}

	std::cout << std::endl;

}

void saveCollectionToBinary(const char* fileName, const JediCollection& collection)
{

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file.write((const char*)&collection, collection.countOfJedis * sizeof(Jedi));
	file.close();

}

JediCollection readCollectionFromBinary(const char* fileName)
{

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return {};

	JediCollection result;
	result.countOfJedis = HELPERS::getFileSize(file) / sizeof(Jedi);

	file.read((char*)&result, result.countOfJedis * sizeof(Jedi));
	file.close();

	return result;

}

void saveJediToTxt(std::ofstream& file, const Jedi& jedi)
{

	file << jedi.name << " ";
	file << jedi.age << " ";
	file << jedi.power << " ";
	file << (int)jedi.saber.color << " ";
	file << (int)jedi.saber.type << " ";
	file << std::endl;

}

void saveCollectionToTxt(const char* fileName, const JediCollection& collection)
{

	std::ofstream file(fileName);

	if (!file.is_open()) return;

	for (int i = 0; i < collection.countOfJedis; i++)
	{

		saveJediToTxt(file, collection.jedis[i]);

	}

	file.close();

}

Jedi readJediFromTxt(std::ifstream& file)
{

	Jedi result;

	file >> result.name;
	file >> result.age;
	file >> result.power;

	int number1, number2 = 0;
	file >> number1;
	file >> number2;
	result.saber.color = (Color)number1;
	result.saber.type = (Type)number2;

	file.ignore(1);

	return result;

}

JediCollection readCollectionFromTxt(const char* fileName)
{

	std::ifstream file(fileName);

	if (!file.is_open()) return {};

	JediCollection result;
	result.countOfJedis = HELPERS::getCountOfJedisInTxt(file);

	for (int i = 0; i < result.countOfJedis; i++)
	{

		result.jedis[i] = readJediFromTxt(file);

	}

	file.close();

	return result;

}

typedef bool (*predicate)(const Jedi& j1, const Jedi& j2);

bool byAge(const Jedi& j1, const Jedi& j2)
{

	return j1.age < j2.age;

}

bool ByPower(const Jedi& j1, const Jedi& j2)
{

	return j1.power < j2.power;

}

void sortByPredicate(JediCollection& collection, predicate func)
{

	for (int i = 0; i < collection.countOfJedis - 1; i++)
	{

		for (int j = 0; j < collection.countOfJedis - i - 1; j++)
		{

			if (func(collection.jedis[j], collection.jedis[j + 1]))
			{

				std::swap(collection.jedis[j], collection.jedis[j + 1]);

			}

		}

	}

}

void sortByAge(JediCollection& collection)
{

	sortByPredicate(collection, byAge);

}

void sortByPower(JediCollection& collection)
{

	sortByPredicate(collection, ByPower);

}

Color mostPopularSaberColor(const JediCollection& collection)
{

	int counter[HELPERS::COUNT_OF_COLORS]{ 0 };

	for (int i = 0; i < collection.countOfJedis; i++)
	{

		counter[(int)collection.jedis[i].saber.color] += 1;

	}

	int index = 0;
	int prev = counter[0];

	for (int i = 0; i < HELPERS::COUNT_OF_COLORS; i++)
	{

		if (prev < counter[i])
		{

			index = i;
			prev = counter[i];

		}

	}

	return (Color)index;

}

Type mostPopularSaberType(const JediCollection& collection)
{

	int counter[HELPERS::COUNT_OF_TYPES]{ 0 };

	for (int i = 0; i < collection.countOfJedis; i++)
	{

		counter[(int)collection.jedis[i].saber.type] += 1;

	}

	int index = 0;
	int prev = counter[0];

	for (int i = 0; i < HELPERS::COUNT_OF_TYPES; i++)
	{

		if (prev < counter[i])
		{

			index = i;
			prev = counter[i];

		}

	}

	return (Type)index;

}

int main()
{

	Jedi jedi1 = createJedi("Yoan", 20, 100, { Color::GREEN, Type::DOUBLE_BLADED });
	Jedi jedi2 = createJedi("Ivo", 20, 0, { Color::BLUE, Type::CROSSGUARD });
	Jedi jedi3 = createJedi("Koko", 10, 100, { Color::BLUE, Type::CROSSGUARD });
	Jedi jedi4 = createJedi("PlovDIV", 21, 100, { Color::YELLOW, Type::DOUBLE_BLADED });

	JediCollection collection = { {jedi1, jedi2, jedi3}, 3 };
	printJediCollection(collection);

	addJedi(collection, jedi4);
	printJediCollection(collection);

	removeJedi(collection, "PlovDIV");
	printJediCollection(collection);

	saveCollectionToBinary("../file.dat", collection);

	JediCollection newCollection1 = readCollectionFromBinary("../file.dat");
	printJediCollection(newCollection1);

	saveCollectionToTxt("../test1.txt", collection);
	JediCollection newCollection2 = readCollectionFromTxt("../test1.txt");
	printJediCollection(newCollection2);

	sortByPower(collection);
	printJediCollection(collection);

	Color mostPop = mostPopularSaberColor(collection);
	std::cout << (int)mostPop << std::endl;

	Type mostTyp = mostPopularSaberType(collection);
	std::cout << (int)mostTyp << std::endl;

	return 0;

}
