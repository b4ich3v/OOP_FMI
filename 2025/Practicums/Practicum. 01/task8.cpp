#include <iostream>
#include <unordered_set>
#include <string>

struct Node
{
public:

	char name[11];

};

struct Rib
{
public:

	Node node1;
	Node node2;

};

struct Graph
{
public:

	Rib* ribs;
	int countOfNodes;
	int countOfRibs;

};

Graph readGraph()
{

	Graph result = { nullptr, 0 ,0 };
	std::cin >> result.countOfRibs;
	result.ribs = new Rib[result.countOfRibs];
	std::cin.ignore();

	char** allNames = new char* [result.countOfRibs * 2];
	bool* helper = new bool[result.countOfRibs * 2] {false};
	int index = 0;
	int counter = 0;

	for (int i = 0; i < result.countOfRibs * 2; i++) allNames[i] = new char[11];

	for (int i = 0; i < result.countOfRibs; i++)
	{

		Node node1;
		Node node2;

		std::cin.getline(node1.name, 11);
		std::cin.getline(node2.name, 11);

		strncpy(allNames[index], node1.name, 11);
		strncpy(allNames[index + 1], node2.name, 11);
		index += 2;

		Rib currentRib = { node1 ,node2 };
		result.ribs[i] = currentRib;

	}

	for (int i = 0; i < result.countOfRibs * 2; i++)
	{

		for (int j = i + 1; j < result.countOfRibs * 2; j++)
		{

			if (!strcmp(allNames[i], allNames[j]) && !helper[j])
			{

				helper[j] = true;
				counter += 1;

			}

		}

	}

	for (int i = 0; i < result.countOfRibs * 2; i++)
	{

		delete[] allNames[i];

	}

	delete[] helper;
	delete[] allNames;

	result.countOfNodes = counter;
	return result;

}

void free(Graph& graph)
{

	delete[] graph.ribs;
	graph.ribs = nullptr;
	graph.countOfNodes = 0;
	graph.countOfRibs = 0;

}

Graph addRib(const Node& node1, const Node& node2, Graph& graph)
{

	Rib newRib = { node1 , node2 };
	Graph result;
	result.countOfNodes = graph.countOfNodes;
	result.countOfRibs = graph.countOfRibs + 1;
	result.ribs = new Rib[graph.countOfRibs + 1];

	for (int i = 0; i < graph.countOfRibs; i++)
	{

		result.ribs[i] = graph.ribs[i];

	}

	delete[] graph.ribs;
	result.ribs[graph.countOfRibs] = newRib;
	return result;

}

Graph removeRib(const Rib& rib, Graph& graph)
{

	Graph result;
	result.countOfNodes = graph.countOfNodes;
	result.countOfRibs = graph.countOfRibs - 1;
	result.ribs = new Rib[graph.countOfRibs - 1];

	int index = 0;

	for (int i = 0; i < graph.countOfRibs; i++)
	{

		if (!strcmp(rib.node1.name, graph.ribs[i].node1.name)) continue;
		result.ribs[index] = graph.ribs[i];
		index += 1;

	}

	delete[] graph.ribs;
	return result;

}

void exitAndEnter(const Node& node, const Graph& graph)
{

	int exit = 0;
	int enter = 0;

	for (int i = 0; i < graph.countOfRibs; i++)
	{

		if (!strcmp(node.name, graph.ribs[i].node1.name)) exit += 1;
		else if (!strcmp(node.name, graph.ribs[i].node2.name)) enter += 1;

	}

	std::cout << enter << " " << exit;

}

bool isGraphFull(const Graph& graph)
{

	return graph.countOfRibs == graph.countOfNodes * (graph.countOfNodes - 1);

}

bool checkIfRibExist(const Rib& rib, const Graph& graph)
{

	for (int i = 0; i < graph.countOfRibs; i++)
	{

		if (!strcmp(rib.node1.name, graph.ribs[i].node1.name) &&
			!strcmp(rib.node2.name, graph.ribs[i].node2.name))
		{

			return true;

		}

	}

	return false;

}
