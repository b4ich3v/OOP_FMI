#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS
{

	const int POKEMON_MAX_SIZE_NAME = 50;
	const int MAX_SIZE_BUFFER = 1024;

	int getFileSize(std::ifstream& file)
	{

		int currentPos = file.tellg();
		file.seekg(0, std::ios::end);
		int result = file.tellg();
		file.seekg(currentPos);
		file.clear();

		return result;

	}

	int getCountOfLines(std::ifstream& file)
	{

		int result = 0;
		char buffer[MAX_SIZE_BUFFER];

		while (true)
		{

			file.getline(buffer, MAX_SIZE_BUFFER);
			result += 1;

			if (file.eof()) break;

		}

		file.clear();
		file.seekg(0, std::ios::beg);

		return result;

	}

}

enum class Type
{

	NORMAL = 0,
	FIRE = 1,
	WATER = 2,
	GRASS = 3,
	ELECTRIC = 4,
	GHOST = 5,
	FLYING = 6

};

struct Pokemon
{
public:

	char name[HELPERS::POKEMON_MAX_SIZE_NAME + 1];
	Type type;
	int power;

};

Pokemon readPokemonFromConsole()
{

	Pokemon result;

	std::cin >> result.name;
	int number = 0;
	std::cin >> number;
	result.type = (Type)number;
	std::cin >> result.power;

	return result;

}

Pokemon readPokemonFromBinaryFile(const char* fileName)
{

	if (!fileName) return {};

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return {};

	Pokemon result;
	file.read((char*)&result, sizeof(Pokemon));
	file.close();

	return result;

}

Pokemon* readPokemonsFromBinartFile(const char* fileName, int& pokemonsCount)
{

	if (!fileName) return {};

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return {};

	pokemonsCount = HELPERS::getFileSize(file) / sizeof(Pokemon);

	Pokemon* result = new Pokemon[pokemonsCount];
	file.read((char*)result, pokemonsCount * sizeof(Pokemon));
	file.close();

	return result;

}

void writePokemonToBinaryFile(const char* fileName, const Pokemon& p)
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file.write((const char*)&p, sizeof(Pokemon));
	file.close();

}

void writePokemonsToBinaryFile(const char* fileName, Pokemon* pks, int count)
{

	if (!fileName) return;

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file.write((const char*)pks, sizeof(Pokemon) * count);
	file.close();

}

struct PokemonHandler
{
public:

	char* fileName;

};

PokemonHandler newPokemonHandler(const char* fileName)
{

	if (!fileName) return {};

	PokemonHandler result;
	result.fileName = new char[strlen(fileName) + 1];
	strncpy(result.fileName, fileName, strlen(fileName));
	result.fileName[strlen(fileName)] = '\0';

	return result;

}

int getSize(const PokemonHandler& ph)
{

	std::ifstream file(ph.fileName, std::ios::binary);

	if (!file.is_open()) return 0;

	return HELPERS::getFileSize(file) / sizeof(Pokemon);

}

Pokemon at(const PokemonHandler& ph, int i)
{

	int size = getSize(ph);

	if (i >= size || i < 0) return {};

	std::ifstream file(ph.fileName, std::ios::binary);

	if (!file.is_open()) return {};

	Pokemon result;
	file.seekg(i * sizeof(Pokemon));
	file.read((char*)&result, sizeof(Pokemon));
	file.close();

	return result;

}

void swap(const PokemonHandler& ph, int i, int j)
{

	int pokemonsCount = 0;
	Pokemon* pks = readPokemonsFromBinartFile(ph.fileName, pokemonsCount);

	if (i < 0 || i > pokemonsCount || j < 0 || j > pokemonsCount) return;

	std::swap(pks[i], pks[j]);
	writePokemonsToBinaryFile(ph.fileName, pks, pokemonsCount);

	delete[] pks;

}

void writePokemonToTxt(const Pokemon& p, std::ofstream& file)
{

	file << p.name << " ";
	file << (int)p.type << " ";
	file << p.power << " ";
	file << std::endl;

}

void textify(const PokemonHandler& ph, const char* fileName)
{

	if (!fileName) return;

	std::ofstream file1(fileName);
	std::ifstream file2(ph.fileName, std::ios::binary);

	if (!file1.is_open() || !file2.is_open()) return;

	int countOfPokemons = HELPERS::getFileSize(file2) / sizeof(Pokemon);
	Pokemon* pks = new Pokemon[countOfPokemons];

	file2.read((char*)pks, countOfPokemons * sizeof(Pokemon));

	for (int i = 0; i < countOfPokemons; i++)
	{

		writePokemonToTxt(pks[i], file1);

	}

	delete[] pks;
	file1.close();
	file2.close();

}

Pokemon readPokemonFromTxt(std::ifstream& file)
{

	Pokemon result;
	file >> result.name;
	int number = 0;
	file >> number;
	result.type = (Type)number;
	file >> result.power;
	file.ignore(1);

	return result;

}

void untextify(PokemonHandler& ph, const char* fileName)
{

	if (!fileName) return;

	std::ifstream file1(fileName);
	std::ofstream file2(ph.fileName, std::ios::binary | std::ios::trunc);

	if (!file1.is_open() || !file2.is_open()) return;

	int countOfPokemons = HELPERS::getCountOfLines(file1);
	Pokemon* pks = new Pokemon[countOfPokemons];

	for (int i = 0; i < countOfPokemons; i++)
	{

		pks[i] = readPokemonFromTxt(file1);

	}

	file2.write((const char*)pks, countOfPokemons);

	file1.close();
	file2.close();

}

void printPokemon(const Pokemon& p)
{

	std::cout << p.name << " ";

	switch (p.type)
	{

	case Type::NORMAL: std::cout << "NORMAl "; break;
	case Type::ELECTRIC: std::cout << "ELECTRIC "; break;
	case Type::FIRE: std::cout << "FIRE "; break;
	case Type::FLYING: std::cout << "FLYING "; break;
	case Type::GHOST: std::cout << "GHOST "; break;
	case Type::GRASS: std::cout << "GRASS "; break;
	case Type::WATER: std::cout << "WATER "; break;
	default: break;

	}

	std::cout << p.power << " ";

}

void printPokemons(Pokemon* pks, int countOfPokemons)
{

	for (int i = 0; i < countOfPokemons; i++)
	{

		printPokemon(pks[i]);
		std::cout << std::endl;

	}

	std::cout << std::endl;

}

int main()
{

	Pokemon p1 = { "Yoan", Type::WATER, 100 };
	Pokemon p2 = { "Ivo", Type::FIRE, 0 };
	Pokemon p3 = { "Koki", Type::GRASS, 97 };
	Pokemon p4 = { "Ilian", Type::ELECTRIC, 35 };

	Pokemon* pks = new Pokemon[4];
	pks[0] = p1;
	pks[1] = p2;
	pks[2] = p3;
	pks[3] = p4;

	printPokemons(pks, 4);

	writePokemonsToBinaryFile("../file.dat", pks, 4);
	PokemonHandler pksFile = newPokemonHandler("../file.dat");

	Pokemon pokemonAtIndex1Ve1 = at(pksFile, 1);
	printPokemon(pokemonAtIndex1Ve1);
	std::cout << std::endl;

	swap(pksFile, 0, 1);

	Pokemon pokemonAtIndex1Ve2 = at(pksFile, 1);
	printPokemon(pokemonAtIndex1Ve2);
	std::cout << std::endl;

	textify(pksFile, "../test1.txt");

	delete[] pksFile.fileName;
	delete[] pks;

	return 0;

}
