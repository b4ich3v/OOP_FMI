#include <iostream>
#include <cstring>
#pragma once

struct Node 
{
public:

	char* data = nullptr;
	int size = 0;
	int refCounter = 0;

	Node() = default;

	Node(const Node& other) = delete;

	Node& operator = (const Node& other);

	~Node() = default;

	const char* getData() const;

	void allocateData(const char* data);

	void releaseData();

};

class StringPool
{
private:

	Node* nodes = nullptr;
	int countOfNodes = 0;
	int capacity = 8;

	void free();

	void resize(int newCapacity);

	int getFirstFreeIndex() const;

	int getCurrentIndex(const char* str) const;

	void addToPool(int index, const char* str);

	const char* removeFromPool(int index);

public:

	StringPool();

	StringPool(const StringPool& other) = delete;

	StringPool& operator = (const StringPool) = delete;

	~StringPool();

	int getCountOfNodes() const;

	void chainString(const char* str);

	const char* unchainString(const char* str);

	void printPool() const;

};

