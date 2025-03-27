#include <iostream>
#include <cstring>

namespace HELPERS
{

	const int MAX_SIZE_MAGIC_CARD_NAME = 25;
	const int MAX_SIZE_MAGIC_CARD_EFFECT = 100;

	const int MAX_SIZE_MONSTER_CARDS = 20;
	const int MAX_SIZE_MAGIC_CARDS = 20;

}

enum class TypeOfMagicCard
{

	trap = 0, 
	buff = 1, 
	spel = 2

};

class MonsterCard
{
private:

	char* name = nullptr;
	unsigned int atackintPoints = 0;
	unsigned int defensivePoints = 0;

	void copyFrom(const MonsterCard& other)
	{

		delete[] name;
		name = new char[strlen(other.name) + 1];
		strncpy(name, other.name, strlen(other.name));
		name[strlen(other.name)] = '\0';

		atackintPoints = other.atackintPoints;
		defensivePoints = other.defensivePoints;

	}

	void free() 
	{

		delete[] name;
		name = nullptr;

		atackintPoints = 0;
		defensivePoints = 0;

	}

public:

	MonsterCard() = default;

	MonsterCard(const char* name, unsigned int atackintPoints, unsigned int defensivePoints) 
	{

		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		this->atackintPoints = atackintPoints;
		this->defensivePoints = defensivePoints;

	}

	MonsterCard(const MonsterCard& other)
	{

		copyFrom(other);

	}

	MonsterCard& operator = (const MonsterCard& other)
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~MonsterCard()
	{

		free();

	}

};

struct MagicCard 
{
public:

	char name[HELPERS::MAX_SIZE_MAGIC_CARD_NAME + 1] = "Default Name";
	char effect[HELPERS::MAX_SIZE_MAGIC_CARD_EFFECT + 1] = "Default Effect";
	TypeOfMagicCard type = TypeOfMagicCard::buff;

	MagicCard(const char* name, const char* effect, TypeOfMagicCard type) 
	{

		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

		strncpy(this->effect, effect, strlen(effect));
		this->effect[strlen(effect)] = '\0';

		this->type = type;

	}

	MagicCard() = default;

};

class Deck
{
private:

	MonsterCard monsters[HELPERS::MAX_SIZE_MONSTER_CARDS];
	MagicCard magics[HELPERS::MAX_SIZE_MAGIC_CARDS];

	int countOfMonsters = 20;
	int countOfMagics = 20;

public:

	Deck() = default;

	int getCountOfMonsters() const 
	{

		return countOfMonsters;

	}

	int getCountOfMagics() const
	{

		return countOfMagics;

	}

	void addMonster(const MonsterCard& monster) 
	{

		if (countOfMonsters == HELPERS::MAX_SIZE_MONSTER_CARDS) return;

		monsters[countOfMonsters] = monster;
		countOfMonsters += 1;

	}

	void addMagic(const MagicCard& magic)
	{

		if (countOfMagics == HELPERS::MAX_SIZE_MAGIC_CARDS) return;

		magics[countOfMagics] = magic;
		countOfMagics += 1;

	}

	void changeMonsterAt(int index, const MonsterCard& monster) 
	{

		if (index < 0 || index >= countOfMonsters) throw std::logic_error("Error");

		monsters[index] = monster;

	}

	void changeMonsterAt(int index, const char* name, unsigned int atackintPoints, unsigned int defensivePoints)
	{

		MonsterCard monster(name, atackintPoints, defensivePoints);
		changeMonsterAt(index, monster);

	}

	void changeMagicAt(int index, const char* name, const char* effect, TypeOfMagicCard type)
	{

		MagicCard magic(name, effect, type);
		changeMagicAt(index, magic);

	}

	void changeMagicAt(int index, const MagicCard& magic)
	{

		if (index < 0 || index >= countOfMagics) throw std::logic_error("Error");

		magics[index] = magic;

	}

	void removeMonsterAt(int index) 
	{

		std::swap(monsters[index], monsters[countOfMonsters - 1]);
		countOfMonsters -= 1;

	}

	void removeMagicAt(int index)
	{

		std::swap(magics[index], magics[countOfMagics - 1]);
		countOfMagics -= 1;

	}

};

class Duelist
{
private:

	char* name = nullptr;
	Deck deck;

	void copyFrom(const Duelist& other) 
	{

		delete[] name;
		name = new char[strlen(other.name) + 1];
		strncpy(name, other.name, strlen(other.name));
		name[strlen(other.name)] = '\0';

		deck = other.deck;

	}

	void free()
	{

		delete[] name;
		name = nullptr;

	}

public:

	Duelist(const char* name)
	{

		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';

	}

	Duelist(const Duelist& other) 
	{

		copyFrom(other);

	}

	Duelist& operator = (const Duelist& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Duelist() 
	{

		free();

	}

	void addMonster(const MonsterCard& monster)
	{

		if (deck.getCountOfMonsters() == HELPERS::MAX_SIZE_MONSTER_CARDS) return;

		deck.addMonster(monster);

	}

	void addMagic(const MagicCard& magic)
	{

		if (deck.getCountOfMagics() == HELPERS::MAX_SIZE_MAGIC_CARDS) return;

		deck.addMagic(magic);

	}

	void changeMonsterAt(int index, const MonsterCard& monster)
	{

		if (index < 0 || index >= deck.getCountOfMonsters()) throw std::logic_error("Error");

		deck.changeMonsterAt(index, monster);

	}

	void changeMagicAt(int index, const MagicCard& magic)
	{

		if (index < 0 || index >= deck.getCountOfMagics()) throw std::logic_error("Error");

		deck.changeMagicAt(index, magic);

	}

	void removeMonsterAt(int index)
	{

		deck.removeMonsterAt(index);

	}

	void removeMagicAt(int index)
	{

		deck.removeMagicAt(index);

	}

};

int main()
{

	Deck deck;

	deck.changeMonsterAt(4, "Blue-eyes white dragon", 3000, 2500);

	deck.changeMagicAt(5, "Monster reborn", "revive", TypeOfMagicCard::spel);

	std::cout << deck.getCountOfMagics() << std::endl;
	std::cout << deck.getCountOfMonsters() << std::endl;

	Duelist player1("Seto Kaiba");
	MonsterCard DarkMagician("Dark Magician", 2500, 2100);

	player1.changeMonsterAt(2, DarkMagician);

	Duelist player2("Yugi Muto");
	MagicCard Reflection("Reflection", "Reflects the last played spell", TypeOfMagicCard::trap);
	player2.changeMagicAt(2, Reflection);

	return 0;

}
