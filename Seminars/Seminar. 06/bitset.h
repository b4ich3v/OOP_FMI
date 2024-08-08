#pragma once

class Bitset 
{
private:

	char* data;
	int buckets;
	int capacity;

	void resize();

	void free();

	void copyFrom(const Bitset& other);

	int getIndex(int number) const;

	int getBucket(int number) const;

public:

	Bitset();

	Bitset(int number);

	Bitset(const Bitset& other);

	Bitset& operator = (const Bitset& other);

	~Bitset();

	void addNumber(int number);

	void removeNumber(int number);

	bool hasNumber(int number) const;

	void print() const;

	friend Bitset Union(const Bitset& lhs, const Bitset& rhs);

	friend Bitset Intersect(const Bitset& lhs, const Bitset& rhs);

};

