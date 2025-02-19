#include <iostream>

struct Node
{
public:

	char name[11];

};

struct Edge
{
public:

	Node node1;
	Node node2;

};

struct Graph
{
public:

	Edge* edges;
	int countOfNodes;
	int countOfEdges;

};

Graph readGraph()
{

	Graph result = { nullptr, 0 ,0 };
	std::cin >> result.countOfEdges;
	result.edges = new Edge[result.countOfEdges];
	std::cin.ignore();

	char** allNames = new char* [result.countOfEdges * 2];
	bool* helper = new bool[result.countOfEdges * 2] {false};
	int index = 0;
	int counter = 0;

	for (int i = 0; i < result.countOfEdges * 2; i++) allNames[i] = new char[11];

	for (int i = 0; i < result.countOfEdges; i++)
	{

		Node node1;
		Node node2;

		std::cin.getline(node1.name, 11);
		std::cin.getline(node2.name, 11);

		strncpy(allNames[index], node1.name, 11);
		strncpy(allNames[index + 1], node2.name, 11);
		index += 2;

		Edge currentRib = { node1 ,node2 };
		result.edges[i] = currentRib;

	}

	for (int i = 0; i < result.countOfEdges * 2; i++)
	{

		for (int j = i + 1; j < result.countOfEdges * 2; j++)
		{

			if (!strcmp(allNames[i], allNames[j]) && !helper[j])
			{

				helper[j] = true;
				counter += 1;

			}

		}

	}

	for (int i = 0; i < result.countOfEdges * 2; i++)
	{

		delete[] allNames[i];

	}

	delete[] helper;
	delete[] allNames;

	result.countOfNodes = result.countOfEdges * 2 - counter;
	return result;

}

void free(Graph& graph)
{

	delete[] graph.edges;
	graph.edges = nullptr;
	graph.countOfNodes = 0;
	graph.countOfEdges = 0;

}

Graph addEdge(const Node& node1, const Node& node2, Graph& graph)
{

	Edge newEdge = { node1 , node2 };
	Graph result;
	result.countOfNodes = graph.countOfNodes;
	result.countOfEdges = graph.countOfEdges + 1;
	result.edges = new Edge[graph.countOfEdges + 1];

	for (int i = 0; i < graph.countOfEdges; i++)
	{

		result.edges[i] = graph.edges[i];

	}

	delete[] graph.edges;
	result.edges[graph.countOfEdges] = newEdge;
	return result;

}

Graph removeEdge(const Edge& edge, Graph& graph)
{

	Graph result;
	result.countOfNodes = graph.countOfNodes;
	result.countOfEdges = graph.countOfEdges - 1;
	result.edges = new Edge[graph.countOfEdges - 1];

	int index = 0;

	for (int i = 0; i < graph.countOfEdges; i++)
	{

		if (!strcmp(edge.node1.name, graph.edges[i].node1.name)) continue;
		result.edges[index] = graph.edges[i];
		index += 1;

	}

	delete[] graph.edges;
	return result;

}

void exitAndEnter(const Node& node, const Graph& graph)
{

	int exit = 0;
	int enter = 0;

	for (int i = 0; i < graph.countOfEdges; i++)
	{

		if (!strcmp(node.name, graph.edges[i].node1.name)) exit += 1;
		else if (!strcmp(node.name, graph.edges[i].node2.name)) enter += 1;

	}

	std::cout << enter << " " << exit;

}

bool isGraphFull(const Graph& graph)
{

	return graph.countOfEdges == graph.countOfNodes * (graph.countOfNodes - 1);

}

bool checkIfEdgeExist(const Edge& edge, const Graph& graph)
{

	for (int i = 0; i < graph.countOfEdges; i++)
	{

		if (!strcmp(edge.node1.name, graph.edges[i].node1.name) &&
			!strcmp(edge.node2.name, graph.edges[i].node2.name))
		{

			return true;

		}

	}

	return false;

}
