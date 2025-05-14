#include <iostream>
#include "HeterogeneousContainer.hpp"
#include "MyString.h"

static bool fightingMask = false;
const constexpr uint8_t specValue = 3;

class Minotaur;

class Centaur;

class Sphynx;

class Creature 
{
public:

	virtual bool fightAgainstCreature(const Creature* ptr) const = 0;

	virtual bool fightAgainstMinotaur(const Minotaur* ptr) const = 0;

	virtual bool fightAgainstCentaur(const Centaur* ptr) const = 0;

	virtual bool fightAgainstSphynx(const Sphynx* ptr) const = 0;

	virtual Creature* clone() const = 0;

	virtual ~Creature() = default;

};

class Minotaur: public Creature 
{
public:

	bool fightAgainstCreature(const Creature* other) const override 
	{
		
		return other->fightAgainstMinotaur(this);

	}

	bool fightAgainstMinotaur(const Minotaur* ptr) const override 
	{

		fightingMask = !fightingMask;
		return fightingMask == true;

	}

	bool fightAgainstCentaur(const Centaur* ptr) const 
	{

		return false;

	}

	bool fightAgainstSphynx(const Sphynx* ptr) const override 
	{

		return true;

	}

	Creature* clone() const override 
	{

		return new Minotaur(*this);

	}

};

class Centaur: public Creature
{
public:

	bool fightAgainstCreature(const Creature* other) const override
	{

		return other->fightAgainstCentaur(this);

	}

	bool fightAgainstMinotaur(const Minotaur* ptr) const override
	{

		return true;

	}

	bool fightAgainstCentaur(const Centaur* ptr) const
	{

		fightingMask = !fightingMask;
		return fightingMask == true;

	}

	bool fightAgainstSphynx(const Sphynx* ptr) const override
	{

		return false;

	}

	Creature* clone() const override
	{

		return new Centaur(*this);

	}

};

class Sphynx: public Creature
{
public:

	bool fightAgainstCreature(const Creature* other) const override
	{

		return other->fightAgainstSphynx(this);

	}

	bool fightAgainstMinotaur(const Minotaur* ptr) const override
	{

		return false;

	}

	bool fightAgainstCentaur(const Centaur* ptr) const
	{

		return true;

	}

	bool fightAgainstSphynx(const Sphynx* ptr) const override
	{

		fightingMask = !fightingMask;
		return fightingMask == true;

	}

	Creature* clone() const override
	{

		return new Sphynx(*this);

	}

};

template <class T, class N>

struct ManipulationPair
{
public:

	T first;
	N second;

	ManipulationPair() = default;

	ManipulationPair(const T& first, const N& second): first(first), second(second) {}

};

template <class T>

int fightingMethod(const HeterogeneousContainer<T>& arr, size_t index) 
{

	int counter = 0;

	for (int i = 0; i < arr.getSize(); i++)
	{

		if (i == index) continue;
		if (arr[index]->fightAgainstCreature(arr[i])) counter += 1;

	}

	return counter;

}

int main() 
{

	HeterogeneousContainer<Creature> arena;

	for (int i = 0; i < 15; ++i) 
	{

		switch (i % 3) 
		{

		case 0: arena.addElement(Minotaur()); break;
		case 1: arena.addElement(Centaur()); break;
		case 2: arena.addElement(Sphynx()); break;
		default: break;

		}

	}

	size_t fighterIndex = 5;

	try
	{

		int wins = fightingMethod(arena, fighterIndex);
		std::cout << "Creature at index " << fighterIndex
			<< " wins against " << wins << " opponents" << std::endl;

	}
	catch (std::exception& e) 
	{

		std::cout << "Error: " << e.what() << std::endl;
		return 1;

	}

	return 0;

}
