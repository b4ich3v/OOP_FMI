#include "DeskOfUnoCards.h"

void DeskOfUnoCards::free() 
{

	for (int i = 0; i < countOfCards; i++)
	{

		delete cards[i];
		cards[i] = nullptr;

	}

	delete[] cards;
	cards = nullptr;
	countOfCards = 0;
	capacity = 8;

}

void DeskOfUnoCards::resize(int newCapacity) 
{

	if (newCapacity <= capacity) return;

	UnoCard** newUnoCard = new UnoCard * [newCapacity] {nullptr};

	for (int i = 0; i < countOfCards; i++)
	{

		newUnoCard[i] = cards[i];

	}

	delete[] cards;
	cards = newUnoCard;
	capacity = newCapacity;

}

void DeskOfUnoCards::copyFrom(const DeskOfUnoCards& other) 
{

	this->cards = new UnoCard * [other.capacity] {nullptr};
	this->countOfCards = other.countOfCards;
	this->capacity = other.capacity;

	for (int i = 0; i < countOfCards; i++)
	{

		this->cards[i] = other.cards[i]->clone();

	}

}

void DeskOfUnoCards::moveTo(DeskOfUnoCards&& other) 
{

	this->cards = other.cards;
	this->capacity = other.capacity;
	this->countOfCards = other.countOfCards;

	other.cards = nullptr;
	other.capacity = 8;
	other.countOfCards = 0;

}

DeskOfUnoCards::DeskOfUnoCards() 
{

	capacity = 8;
	cards = new UnoCard * [capacity] {nullptr};

}

DeskOfUnoCards::DeskOfUnoCards(const DeskOfUnoCards& other) 
{

	copyFrom(other);

}

DeskOfUnoCards::DeskOfUnoCards(DeskOfUnoCards&& other) noexcept 
{

	moveTo(std::move(other));

}

DeskOfUnoCards& DeskOfUnoCards::operator = (const DeskOfUnoCards& other)
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

DeskOfUnoCards& DeskOfUnoCards::operator = (DeskOfUnoCards&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

DeskOfUnoCards::~DeskOfUnoCards() 
{

	free();

}

void DeskOfUnoCards::addCard(const UnoCard* card)
{

	if (countOfCards == capacity) resize(capacity * 2);

	cards[countOfCards] = card->clone(); 
	countOfCards += 1;

}

void DeskOfUnoCards::removeCard(const DigitUnoCard& card)
{

	bool found = false;

	for (int i = 0; i < countOfCards; i++)
	{

		if (cards[i]->getColor() == card.getColor() &&
			cards[i]->isDigitUnoCard(&card))
		{

			std::swap(cards[countOfCards - 1], cards[i]);
			countOfCards -= 1;
			found = true;
			break;

		}

	}

	if (!found) addCard(&card);

}

void DeskOfUnoCards::printDesk() const 
{

	for (int i = 0; i < countOfCards; i++)
	{

		cards[i]->printCard(cards[i]);

	}

	std::cout << std::endl;

}
