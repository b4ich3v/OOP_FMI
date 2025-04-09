#include <iostream>
#include <cstring>

class StringPool
{
private:

	struct Node 
	{

		char* data = nullptr;
		int refCounter = 0;

		Node() = default;

		Node& operator = (const Node& other) 
		{

			if (this != &other) 
			{

				delete[] data;
				this->data = new char[strlen(other.data) + 1];
				strncpy(this->data, other.data, strlen(other.data));
				this->data[strlen(other.data)] = '\0';
				refCounter = other.refCounter;

			}

			return *this;

		}

		Node(const Node& other) 
		{

			this->data = new char[strlen(other.data) + 1];
			strncpy(this->data, other.data, strlen(other.data));
			this->data[strlen(other.data)] = '\0';
			refCounter = other.refCounter;

		}

		~Node() 
		{

			delete[] data;
			data = nullptr;

		}

		void allocateData(const char* data)
		{

			this->data = new char[strlen(data) + 1];
			strncpy(this->data, data, strlen(data));
			this->data[strlen(data)] = '\0';
			refCounter = 1;

		}

	};

	Node* nodes = nullptr;
	int countOfNodes = 0;
	int capacity = 8;

	void free() 
	{

		delete[] nodes;
		nodes = nullptr;
		
	}

	void resize(int newCapacity) 
	{

		Node* newNodes = new Node[newCapacity];

		for (int i = 0; i < countOfNodes; i++)
		{

			newNodes[i] = nodes[i];

		}

		delete[] nodes;
		nodes = newNodes;
		capacity = newCapacity;

	}

	int findString(const char* str) 
	{

		int index = -1;

		for (int i = 0; i < countOfNodes; i++)
		{

			if (!strcmp(nodes[i].data, str)) 
			{

				index = i;
				break;

			}

		}

		return index;

	}

	void removeFromPool(int index) 
	{

		for (int i = index; i < countOfNodes - 1; i++)
		{

			nodes[i] = nodes[i + 1];

		}

		countOfNodes -= 1;

	}

	void addStringToPool(const char* str) 
	{

		if (countOfNodes == capacity) resize(capacity * 2);
		nodes[countOfNodes].allocateData(str);
		countOfNodes += 1;

	}

public:

	StringPool()
	{

		countOfNodes = 0;
		capacity = 8;
		nodes = new Node[capacity];

	}

	StringPool& operator = (const StringPool& other) = delete;

	StringPool(const StringPool& other) = delete;

	~StringPool()
	{

		free();

	}

	const char* getString(const char* str) 
	{

		int index = findString(str);

		if (index == -1)
		{

			addStringToPool(str);
			return nodes[countOfNodes - 1].data;

		}
		else
		{

			nodes[index].refCounter += 1;
			return nodes[index].data;

		}

	}

	void removeString(const char* str) 
	{

		int index = findString(str);

		if (index == -1) throw std::logic_error("Already removed");
		else
		{

			nodes[index].refCounter -= 1;
			if (nodes[index].refCounter == 0) removeFromPool(index);

		}
		
	}

	void printPool() const 
	{

		for (int i = 0; i < countOfNodes; i++)
		{

			std::cout << nodes[i].data << " " << nodes[i].refCounter << std::endl;

		}

		std::cout << std::endl;

	}

};

int main()
{

	StringPool pool;
	pool.getString("Yoan");
	pool.getString("Yoan");
	pool.getString("Yoan");
	pool.getString("Ivailo1");
	pool.getString("Ivailo2");
	pool.getString("1");
	pool.getString("2");
	pool.getString("3");
	pool.getString("4");
	pool.getString("5");
	pool.getString("6");
	pool.getString("7");
	pool.removeString("Yoan");
	pool.removeString("3");
	pool.printPool();

	return 0;

}



