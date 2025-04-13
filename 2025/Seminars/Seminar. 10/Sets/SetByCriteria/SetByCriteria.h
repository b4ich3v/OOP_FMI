#include "BitSet.h"
#pragma once

typedef bool (*predicate)(int);

class SetByCriteria: private BitSet
{
private:

	predicate funciton = nullptr;

	void fillSet(int bound);

public:

	SetByCriteria(int number, predicate func);

	bool hasCurrentNumber(int number) const;

	void print() const;

};

