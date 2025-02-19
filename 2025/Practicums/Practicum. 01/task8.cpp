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

	std::unordered_set<std::string> s;

	for (int i = 0; i < result.countOfRibs; i++)
	{

		Node node1;
		Node node2;

		std::cin.getline(node1.name, 11);
		std::cin.getline(node2.name, 11);

		Rib currentRib = { node1 ,node2 };
		result.ribs[i] = currentRib;
		s.insert(node1.name);
		s.insert(node2.name);

	}

	result.countOfNodes = s.size();
	return result;

}

void free(Graph& graph)
{

	delete[] graph.ribs;
	graph.ribs = nullptr;
	graph.countOfNodes = 0;
	graph.countOfRibs = 0;

}

Graph addRib(const Node& node1, const Node& node2, const Graph& graph)
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

Graph removeRib(const Rib& rib, const Graph& graph)
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
