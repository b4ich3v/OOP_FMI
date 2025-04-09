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

class ImmutableString
{
private:

	static StringPool pool;

	const char* data = nullptr;
	int size = 0;

public:

	ImmutableString& operator = (const ImmutableString& other) = delete;

	ImmutableString(const char* data) 
	{

		this->data = pool.getString(data);
		size = strlen(data);

	}

	ImmutableString(const ImmutableString& other) 
	{

		data = pool.getString(other.c_str());
		size = strlen(other.data);

	}

	~ImmutableString()
	{

		pool.removeString(data);
		size = 0;

	}

	const char* c_str() const
	{

		return data;

	}

	int getSize() const 
	{

		return size;

	}

	friend ImmutableString operator + (const ImmutableString& str1, const ImmutableString& str2) 
	{

		char* newData = new char[str1.getSize() + str2.getSize() + 1];
		strncpy(newData, str1.c_str(), str1.getSize());
		strcat(newData, str2.c_str());
		newData[str1.getSize() + str2.getSize()] = '\0';

		ImmutableString result(newData);
		delete[] newData;

		return result;

	}

	friend std::ostream& operator << (std::ostream& os, const ImmutableString& str) 
	{

		os << str.c_str();
		return os;

	}

	static void printPoolFromStr() 
	{

		pool.printPool();

	}

};

StringPool ImmutableString::pool;  

bool operator == (const ImmutableString& str1, const ImmutableString& str2) 
{

	return !strcmp(str1.c_str(), str2.c_str());

}

bool operator != (const ImmutableString& str1, const ImmutableString& str2)
{

	return !(str1 == str2);

}

bool operator > (const ImmutableString& str1, const ImmutableString& str2)
{

	return strcmp(str1.c_str(), str2.c_str()) > 0;

}

bool operator < (const ImmutableString& str1, const ImmutableString& str2)
{

	return strcmp(str1.c_str(), str2.c_str()) < 0;

}

bool operator >= (const ImmutableString& str1, const ImmutableString& str2)
{

	return !(str1 < str2);

}

bool operator <= (const ImmutableString& str1, const ImmutableString& str2)
{

	return !(str1 > str2);

}

int main()
{

	ImmutableString str1("Yoan");
	ImmutableString str2("Yoan");
	ImmutableString str5 = str1;
	str1.printPoolFromStr();

	{

		ImmutableString str3("Yoan");
		ImmutableString str4("Yoan");
		ImmutableString::printPoolFromStr();

	}


	{

		ImmutableString str6 = "1";
		ImmutableString str7 = "2";
		ImmutableString str8 = "3";
		ImmutableString str9 = "4";
		ImmutableString::printPoolFromStr();

	}

	ImmutableString str10 = "1";
	ImmutableString res = str1 + str10;
	ImmutableString::printPoolFromStr();

	std::cout << res << std::endl;
	
	return 0;

}


