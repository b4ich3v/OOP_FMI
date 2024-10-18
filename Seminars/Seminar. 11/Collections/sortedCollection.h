#pragma once
#include "pureNumbersCollection.h"

class SortedCollection : public PureNumbersCollection
{
private:

	int lowerBound(int x) const;

	int upperBound(int x) const;

public:

	void add(int) override;

	void remove(int) override;

	unsigned count(int) const override;

	bool contains(int) const override;

};
