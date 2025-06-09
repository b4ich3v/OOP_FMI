#include "Set.hpp"
#pragma once

class EvenNumbers: public Set<int>
{
public:

	Set<int>* clone() const override;

	void serialize(std::ostream& os) const override;

	void deserialize(std::istream& is) override;

	bool member(const int& element) const override;

};

Set<int>* EvenNumbers::clone() const
{

	return new EvenNumbers(*this);

}

bool EvenNumbers::member(const int& element) const
{

	return element % 2 == 0;

}

void EvenNumbers::serialize(std::ostream& os) const
{

	os << "{EvenNumbers}";

}

void EvenNumbers::deserialize(std::istream& is)
{

	return;

}
