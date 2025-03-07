#include <iostream>
#include <fstream>
#include <cstdint>

namespace HELPERS
{

	const int SIZE_OF_NODE = 512;
	const int SIZE_OF_NODE_DATA = 504;
	const int MASK = 0b0;

	int getFileSize(std::ifstream& file)
	{

		int currentPos = file.tellg();
		file.seekg(0, std::ios::end);
		int result = file.tellg();
		file.seekg(currentPos);
		file.clear();

		return result;

	}

}

struct Node
{
public:

	char user_data[HELPERS::SIZE_OF_NODE_DATA];
	uint64_t next;

};

struct NodeContainer
{
public:

	Node* nodes;
	int size;

};

Node parserForNode(std::ifstream& file)
{

	Node result;
	file.read((char*)&result, HELPERS::SIZE_OF_NODE);

	return result;

}

void lowerAllTheBits(Node& censoredNode)
{

	for (int i = 0; i < HELPERS::SIZE_OF_NODE_DATA; i++)
	{

		censoredNode.user_data[i] &= HELPERS::MASK;

	}

}

void censorUnusedNodes(const char* fileName, const NodeContainer& collection, bool* array)
{

	std::ofstream file(fileName, std::ios::binary);
	if (!file.is_open()) return;

	for (int i = 0; i < collection.size; i++)
	{

		if (!array[i])
		{

			lowerAllTheBits(collection.nodes[i]);

			file.seekp(i * HELPERS::SIZE_OF_NODE, std::ios::beg);
			file.write((const char*)&collection.nodes[i], HELPERS::SIZE_OF_NODE);

		}

	}

	file.close();

}

void fillBooleanArray(bool* array, int size, const NodeContainer& collection)
{

	array[0] = true;

	for (int i = 0; i < size; i++)
	{

		uint64_t nextIndex = collection.nodes[i].next;

		if (nextIndex > 0 && nextIndex < size)
		{

			array[nextIndex] = true;

		}

	}

}

void parserForNodeContainer(const char* fileName)
{

	if (!fileName) return;

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	NodeContainer collection;
	collection.size = HELPERS::getFileSize(file) / HELPERS::SIZE_OF_NODE;
	collection.nodes = new Node[collection.size];

	for (int i = 0; i < collection.size; i++)
	{

		collection.nodes[i] = parserForNode(file);

	}

	bool* array = new bool[collection.size] {false};
	fillBooleanArray(array, collection.size, collection);

	file.close();
	censorUnusedNodes(fileName, collection, array);

	delete[] array;
	delete[] collection.nodes;

}

int main()
{

	parserForNodeContainer("../maintasks.db");
	return 0;

}
