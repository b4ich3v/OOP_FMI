#include "UnoCard.h"
#include "DigitUnoCard.h"
#pragma once

class DeskOfUnoCards
{
private:

	UnoCard** cards = nullptr;
	int countOfCards = 0;
	int capacity = 8;

	void free();

	void resize(int newCapacity);

	void copyFrom(const DeskOfUnoCards& other);

	void moveTo(DeskOfUnoCards&& other);

public:

	DeskOfUnoCards();

	DeskOfUnoCards(const DeskOfUnoCards& other);

	DeskOfUnoCards(DeskOfUnoCards&& other) noexcept;

	DeskOfUnoCards& operator = (const DeskOfUnoCards& other);

	DeskOfUnoCards& operator = (DeskOfUnoCards&& other) noexcept;

	~DeskOfUnoCards();

	void addCard(const UnoCard* card);

	void removeCard(const DigitUnoCard& card);

	void printDesk() const;

};


