#include <iostream>
#include "MyString.h"

namespace HELPERS
{

	const int MAX_SIZE_BUFFER = 1024;

	bool isDigit(char ch)
	{

		return ch >= '0' && ch <= '9';

	}

	bool isValid(const MyString& str)
	{

		for (int i = 0; i < str.getSize(); i++)
		{

			if (!isDigit(str[i])) return false;

		}

		return true;

	}

	int toDigit(char ch)
	{

		return ch - '0';

	}

	char toChar(int digit)
	{

		return digit + '0';

	}

	void reverseString(MyString& str)
	{

		for (int i = 0; i < str.getSize() / 2; i++)
		{


			std::swap(str[i], str[str.getSize() - i - 1]);

		}

	}

}

class Stack
{
private:

	char* data = nullptr;
	int size = 0;
	int capacity = 8;

	void copyFrom(const Stack& other)
	{

		data = new char[other.capacity];
		capacity = other.capacity;
		size = other.size;

		for (int i = 0; i < size; i++)
		{

			data[i] = other.data[i];

		}

	}

	void free()
	{

		delete[] data;
		data = nullptr;

		size = 0;
		capacity = 8;

	}

	void resize(int newCapacity)
	{

		if (newCapacity <= capacity) return;

		char* newData = new char[newCapacity];

		for (int i = 0; i < size; i++)
		{

			newData[i] = data[i];

		}

		delete[] data;
		data = newData;
		capacity = newCapacity;

	}

public:

	Stack()
	{

		size = 0;
		capacity = 8;

		data = new char[capacity] {0};

	}

	Stack(const Stack& other)
	{

		copyFrom(other);

	}

	Stack& operator = (const Stack& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Stack()
	{

		free();

	}

	void push(int number)
	{

		if (size == capacity) resize(capacity * 2);

		data[size] = number;
		size += 1;

	}

	void pop()
	{

		if (size == 0) throw std::logic_error("Error");

		size -= 1;

	}

	char top() const
	{

		if (size == 0) throw std::logic_error("Error");

		return data[size - 1];

	}

	int peek() const
	{

		if (size == 0) throw std::logic_error("Error");

		return data[size - 1];

	}

	bool isEmpty() const
	{

		return size == 0;

	}

};

struct Node
{
public:

	char currentDigit = '0';
	Node* next = nullptr;

	Node() = default;

	Node(char newCurrentDigit, Node* newNext = nullptr) : currentDigit(newCurrentDigit), next(newNext) {}

};

class BigNumber
{
private:

	Node* root = nullptr;
	bool isNegative = false;

	void free()
	{

		Node* toDelete;

		while (root)
		{

			toDelete = root;
			root = root->next;
			delete toDelete;

		}

		isNegative = false;

	}

	void copyFrom(const BigNumber& other)
	{

		Node* newRoot = new Node(other.root->currentDigit);
		Node* currentNew = newRoot;
		Node* currentOther = other.root->next;

		while (currentOther != nullptr)
		{

			currentNew->next = new Node(currentOther->currentDigit);

			currentNew = currentNew->next;
			currentOther = currentOther->next;

		}

		free();
		root = newRoot;
		isNegative = other.isNegative;

	}

	int compareAbsoluteValues(const BigNumber& number) const
	{

		int digits1 = this->getCountOfDigits();
		int digits2 = number.getCountOfDigits();

		if (digits1 < digits2) return -1;
		if (digits1 > digits2) return 1;

		Node* leftNode = this->root;
		Node* rightNode = number.root;

		while (leftNode && rightNode)
		{

			if (leftNode->currentDigit < rightNode->currentDigit) return -1;
			if (leftNode->currentDigit > rightNode->currentDigit) return 1;

			leftNode = leftNode->next;
			rightNode = rightNode->next;

		}

		return 0;

	}

public:

	BigNumber()
	{

		root = new Node('0', nullptr);
		isNegative = false;

	}

	BigNumber(const MyString& str, bool isNegative)
	{

		if (!HELPERS::isValid(str)) throw std::logic_error("Error");

		root = new Node(str[0]);
		Node* currentNode = root;

		int counter = str.getSize();
		int index = 1;

		while (counter != 1)
		{

			currentNode->next = new Node(str[index]);
			currentNode = currentNode->next;

			index += 1;
			counter -= 1;

		}

		this->isNegative = isNegative;

	}

	BigNumber(const BigNumber& other)
	{

		copyFrom(other);

	}

	BigNumber& operator = (const BigNumber& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	BigNumber& operator += (const BigNumber& other)
	{

		if (this->isNegative == other.isNegative) this->addAbsoluteValue(other);
		else
		{

			int comparePredicate = compareAbsoluteValues(other);

			if (comparePredicate == 0)
			{

				this->makeZero();

			}
			else if (comparePredicate > 0)
			{

				this->subtractAbsoluteValue(other);
				if (this->isZero()) this->isNegative = false;

			}
			else
			{

				BigNumber temp = other;
				temp.subtractAbsoluteValue(*this);
				*this = temp;

			}

		}

		return *this;

	}

	BigNumber& operator -= (const BigNumber& other)
	{

		BigNumber copy = other;
		copy.isNegative = !copy.isNegative;
		*this += copy;

		return *this;

	}

	BigNumber& addAbsoluteValue(const BigNumber& other)
	{

		MyString reversedLeft;
		MyString reversedRight;

		Node* iterator1 = this->root;
		Node* iterator2 = other.root;

		while (iterator1 != nullptr)
		{

			reversedLeft += iterator1->currentDigit;
			iterator1 = iterator1->next;

		}

		while (iterator2 != nullptr)
		{

			reversedRight += iterator2->currentDigit;
			iterator2 = iterator2->next;

		}

		HELPERS::reverseString(reversedLeft);
		HELPERS::reverseString(reversedRight);

		BigNumber left(reversedLeft, false);
		BigNumber right(reversedRight, false);

		Node* current1 = left.root;
		Node* current2 = right.root;

		Stack st;
		int carry = 0;

		while (current1 != nullptr || current2 != nullptr || carry != 0)
		{

			int digit1 = 0;
			int digit2 = 0;

			if (current1 != nullptr)
			{

				digit1 = HELPERS::toDigit(current1->currentDigit);
				current1 = current1->next;

			}
			
			if (current2 != nullptr)
			{

				digit2 = HELPERS::toDigit(current2->currentDigit);
				current2 = current2->next;

			}

			int sum = digit1 + digit2 + carry;
			carry = sum / 10;
			int digit = sum % 10;

			st.push(HELPERS::toChar(digit));

		}

		MyString result;

		while (!st.isEmpty())
		{

			result += st.top();
			st.pop();

		}

		bool oldSign = this->isNegative;
		BigNumber temp(result, false);
		*this = temp;
		this->isNegative = oldSign;

		return *this;

	}

	BigNumber& subtractAbsoluteValue(const BigNumber& other)
	{

		MyString reversedLeft;
		MyString reversedRight;

		Node* iterator1 = this->root;
		Node* iterator2 = other.root;

		while (iterator1 != nullptr)
		{

			reversedLeft += iterator1->currentDigit;
			iterator1 = iterator1->next;

		}

		while (iterator2 != nullptr)
		{

			reversedRight += iterator2->currentDigit;
			iterator2 = iterator2->next;

		}

		HELPERS::reverseString(reversedLeft);
		HELPERS::reverseString(reversedRight);

		BigNumber left(reversedLeft, false);
		BigNumber right(reversedRight, false);

		Node* current1 = left.root;
		Node* current2 = right.root;

		Stack st;
		int borrow = 0;

		while (current1 != nullptr || current2 != nullptr || borrow != 0)
		{

			int digit1 = 0;
			int digit2 = 0;

			if (current1 != nullptr)
			{

				digit1 = HELPERS::toDigit(current1->currentDigit);
				current1 = current1->next;

			}
			
			if (current2 != nullptr)
			{

				digit2 = HELPERS::toDigit(current2->currentDigit);
				current2 = current2->next;

			}

			int diff = digit1 - borrow - digit2;

			if (diff < 0)
			{

				diff += 10;
				borrow = 1;

			}
			else
			{

				borrow = 0;

			}

			st.push(HELPERS::toChar(diff));

		}

		MyString result;
		bool leadingZero = true;

		while (!st.isEmpty())
		{

			char currentDigit = st.top();
			st.pop();

			if (leadingZero && currentDigit == '0') continue;

			leadingZero = false;
			result += currentDigit;

		}

		if (result.getSize() == 0) result = "0";

		bool oldSign = this->isNegative;
		BigNumber temp(result, false);
		*this = temp;
		this->isNegative = oldSign;

		return *this;

	}

	~BigNumber()
	{

		free();

	}

	bool isZero() const
	{

		return (getCountOfDigits() == 1 && root->currentDigit == '0');

	}

	void makeZero()
	{

		free();

		root = new Node('0');
		isNegative = false;

	}

	int getCountOfDigits() const
	{

		Node* fictiveNode = root;
		int coutner = 0;

		while (fictiveNode != nullptr)
		{

			coutner += 1;
			fictiveNode = fictiveNode->next;

		}

		return coutner;

	}

	friend std::istream& operator >> (std::istream& is, BigNumber& number)
	{

		number.free();
		bool isNegative = false;

		char fictiveSymbol = ' ';
		is >> fictiveSymbol;
		if (fictiveSymbol == '-') isNegative = true;

		char buffer[HELPERS::MAX_SIZE_BUFFER];
		is.getline(buffer, HELPERS::MAX_SIZE_BUFFER);

		MyString str(buffer);
		BigNumber newNumber(str, isNegative);
		number = newNumber;

		return is;

	}

	friend std::ostream& operator << (std::ostream& os, const BigNumber& number)
	{

		int size = number.getCountOfDigits();
		Node* currentNode = number.root;

		if (number.isNegative) os << '-';
		else os << '+';

		for (int i = 0; i < size; i++)
		{

			os << currentNode->currentDigit;
			currentNode = currentNode->next;

		}

		os << std::endl;

		return os;

	}

};

BigNumber operator + (const BigNumber& number1, const BigNumber& number2)
{

	BigNumber result(number1);
	result += number2;

	return result;

}

BigNumber operator - (const BigNumber& number1, const BigNumber& number2)
{

	BigNumber result(number1);
	result -= number2;

	return result;

}

int main()
{

	BigNumber number1("63278141798179151510515111111111", false);
	BigNumber number2("782900001491411419581510591999999", false);
	BigNumber number3("782900001491411419581510591999999", true);

	std::cout << number1 + number2;
	std::cout << number1 - number2;
	
	std::cout << std::endl;

	std::cout << number1 + number3;
	std::cout << number1 - number3;

	return 0;

}

