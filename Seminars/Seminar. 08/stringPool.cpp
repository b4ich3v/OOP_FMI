#include "stringPool.h"
#include <iostream>
#include <exception>
#include <cstring>

#pragma warning(disable:4996)

void StringPool::StringNode::allocateData(const char* string)
{

	int size = strlen(string);
	data = new char[size + 1];
	strcpy(data, string);

}

void StringPool::resize(int newCapacity)
{

	if (newCapacity <= capacity)
	{

		return;

	}

	StringNode* newNodes = new StringNode[newCapacity];

	for (int i = 0; i < size; i++)
	{

		newNodes[i] = nodes[i];

	}

	delete[] nodes;
	nodes = newNodes;
	capacity = newCapacity;

}

int StringPool::find(const char* string, bool& found) const
{

	int left = 0;
	int right = size - 1;

	while(left <= right)
	{

		int middle = left + (right - left) / 2;
		int compare = strcmp(nodes[middle].data, string);

		if (compare > 0) 
		{

			right = middle - 1;

		}
		else if (compare < 0)
		{

			left = middle + 1;

		}
		else
		{

			found = true;
			return middle;

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

	for (int i = size - 1; i < index; i--)
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

	if (index > size)
	{

		throw std::out_of_range("StringPool::insert invalid index!");

	}

	delete[] nodes[index].data;

	for (int i = index; i < size ; i++)
	{

		nodes[i] = nodes[i + 1];

	}

	nodes[index].data = nullptr;
	nodes[index].referenceCount = 0;

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
	int index = find(string, found);

	if (found)
	{

		nodes[index].referenceCount++;
		return nodes[index].data;

	}

	return insert(string, index);

}

void StringPool::removeString(const char* string)
{

	bool found = false;
	int index = find(string, found);

	if (!found)
	{

		return;

	}

	if(nodes[index].referenceCount == 1)
	{

		removeInternal(index);

	}
	else
	{

		nodes[index].referenceCount--;

	}

}

StringPool::~StringPool() 
{

	for (int i = 0; i < size; i++)
	{

		delete[] nodes[i].data;

	}

	delete[] nodes;
	nodes = nullptr;
	size = 0;
	capacity = 8;

}

void StringPool::debug() const
{

	for (int i = 0; i < size; i++)
	{

		std::cout << nodes[i].data << " ";

	}

	std::cout << std::endl;

}
