#include "StringPool.h"

void Node::allocateData(const char* data) 
{

	if (data == nullptr) 
	{

		this->data = nullptr;
		this->size = 0;
		this->refCounter = 0;

		return;

	}

	this->size = strlen(data);
	this->data = new char[size + 1];
	strncpy(this->data, data, size);
	this->data[size] = '\0';
	this->refCounter = 1;

}

Node& Node::operator=(const Node& other)
{

	if (this == &other) return *this;
		
	releaseData();

	if (other.data != nullptr)
	{

		size = other.size;
		data = new char[size + 1];
		strcpy(data, other.data);  
		refCounter = other.refCounter;

	}
	else
	{

		data = nullptr;
		size = 0;
		refCounter = 0;

	}

	return *this;

}

const char* Node::getData() const 
{

	return data;

}

int StringPool::getFirstFreeIndex() const 
{

	for (int i = 0; i < capacity; i++)
	{

		if (nodes[i].refCounter == 0) return i;

	}

	return -1;

}

int StringPool::getCurrentIndex(const char* str) const
{

	for (int i = 0; i < countOfNodes; i++)
	{

		const char* nodeData = nodes[i].getData();
		if (nodeData != nullptr && strcmp(nodeData, str) == 0) return i;
			
	}

	return -1;

}

void Node::releaseData() 
{

	delete[] data;
	data = nullptr;
	refCounter = 0;
	size = 0;

}

void StringPool::free()
{

	for (int i = 0; i < countOfNodes; i++)
	{

		nodes[i].releaseData();

	}

	delete[] nodes;
	nodes = nullptr;

}

void StringPool::resize(int newCapacity)
{

	if (newCapacity <= capacity) return;

	Node* newNodes = new Node[newCapacity];

	for (int i = 0; i < countOfNodes; i++)
	{

		newNodes[i].allocateData(nodes[i].getData());
		newNodes[i].refCounter = nodes[i].refCounter;

	}

	for (int i = 0; i < countOfNodes; i++)
	{

		nodes[i].releaseData();

	}

	delete[] nodes;
	nodes = newNodes;
	capacity = newCapacity;

}

void StringPool::addToPool(int index, const char* str) 
{

	if (index == -1)
	{

		resize(capacity * 2);
		index = countOfNodes;

	}

	nodes[index].allocateData(str);
	nodes[index].refCounter = 1;
	countOfNodes += 1;

}

const char* StringPool::removeFromPool(int index) 
{

	int size = nodes[index].size;
	char* result = new char[size + 1];
	const char* ptr = nodes[index].getData();

	strncpy(result, ptr, size);
	result[size] = '\0';

	nodes[index].releaseData();
	nodes[index].refCounter = 0;
	countOfNodes -= 1;

	return result;

}

int StringPool::getCountOfNodes() const 
{

	return countOfNodes;

}

void StringPool::chainString(const char* str)
{

	int index = getCurrentIndex(str);

	if (index != -1) nodes[index].refCounter += 1;
	else
	{
		
		if (countOfNodes >= capacity) resize(capacity * 2);

		nodes[countOfNodes].allocateData(str);
		nodes[countOfNodes].refCounter = 1;
		countOfNodes += 1;

	}

}

const char* StringPool::unchainString(const char* str)
{

	int index = getCurrentIndex(str);
	if (index == -1) return nullptr;  

	if (nodes[index].refCounter > 1)
	{

		nodes[index].refCounter -= 1;
		return nodes[index].getData();

	}
	else
	{

		int size = nodes[index].size;
		char* result = new char[size + 1];
		strncpy(result, nodes[index].getData(), size);
		result[size] = '\0';

		nodes[index].releaseData();

		if (index != countOfNodes - 1)
		{

			nodes[index] = nodes[countOfNodes - 1];

		}

		countOfNodes -= 1;

		return result;

	}

}

StringPool::StringPool() 
{

	capacity = 8;
	countOfNodes = 0;
	nodes = new Node[capacity];

}

StringPool::~StringPool() 
{

	free();

}
