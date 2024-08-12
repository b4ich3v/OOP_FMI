#include "stringPool.h"
#include <iostream>
#include <exception>
#include <cstring>

#pragma warning(disable:4996)

void StringPool::resize(int newCapacity)
{

	if (newCapacity <= capacity)
	{
		
		return;

	}

	StringNode* newNodes = new StringNode[newCapacity]{};

	for (int i = 0; i < size; i++) 
	{

		newNodes[i] = nodes[i];

	}

	delete[] nodes;
	nodes = newNodes;
	capacity = newCapacity;

}

int StringPool::find(const char* str, bool& found) const
{

	int left = 0;
	int right = size - 1;

	while (left <= right)
	{

		int middle = (right - left) / 2 + left;
		int compare = strcmp(nodes[middle].data, str);

		if (compare == 0)
		{

			found = true;
			return middle;

		}
		else if (compare > 0)
		{

			right = middle - 1;

		}
		else
		{

			left = middle + 1;

		}

	}

	found = false;
	return left;

}

const char* StringPool::insert(const char* string, int index)
{

	if (index > size) 
	{

		throw std::out_of_range("StringPool::insert invalid index!");

	}
		
	if (size == capacity)
	{

		resize(calculateGrowth());

	}

	for (int i = size - 1; i >= (int)index; i--)
	{

		nodes[i + 1] = nodes[i];

	}
		
	nodes[index].allocateData(string);
	nodes[index].referenceCount = 1;

	size++;
	return nodes[index].data;

}

void StringPool::removeInternal(int index)
{

	if (index >= size)
	{

		throw std::out_of_range("StringPool::removeInternal out of range!");

	}
		
	delete[] nodes[index].data;

	for (int i = index; i < size - 1; i++)
	{

		nodes[i] = nodes[i + 1];

	}

	nodes[size - 1].data = nullptr;
	nodes[size - 1].referenceCount = 0;

	size--;

}

int StringPool::calculateGrowth() const
{

	return capacity + capacity / 2;

}

StringPool::StringPool() : nodes(nullptr), size(0), capacity(0) 
{

	resize(8);

}

const char* StringPool::getString(const char* string)
{

	bool found = false;
	int currentIndex = find(string, found);

	if (found)
	{

		nodes[currentIndex].referenceCount++;
		return nodes[currentIndex].data;

	}

	return insert(string, currentIndex);

}

void StringPool::removeString(const char* string)
{

	bool found = false;
	int idx = find(string, found);

	if (!found) 
	{

		return;

	}

	if (nodes[idx].referenceCount == 1)
	{

		removeInternal(idx);

	}
	else
	{

		nodes[idx].referenceCount--;

	}

}

void StringPool::debug() const
{

	for (int i = 0; i < size; i++)
	{

		std::cout << nodes[i].data << " ";

	}

	std::cout << std::endl;

}

StringPool::~StringPool()
{

	for (int i = 0; i < size; i++)
	{

		delete[] nodes[i].data;

	}

	delete[] nodes;

}

void StringPool::StringNode::allocateData(const char* string)
{

	int size = strlen(string);
	data = new char[size + 1] {};
	strcpy(data, string);

}
