#pragma once
#include <cstring>

class StringPool
{
private:

	struct StringNode
	{

		char* data = nullptr;
		int referenceCount = 0;

		void allocateData(const char* string);

	};

	StringNode* nodes;
	int size;
	int capacity;

	void resize(int newCapacity);

	int find(const char* string, bool& found) const;

	const char* insert(const char* string, int index);

	void removeInternal(int index);

	int calculateGrowth() const;

public:

	StringPool();

	StringPool(const StringPool& other) = delete;

	StringPool operator = (const StringPool& other) = delete;

	const char* getString(const char* string);

	void removeString(const char* string);

	void debug() const;

	~StringPool();

};
