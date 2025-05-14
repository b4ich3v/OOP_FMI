#include <iostream>
#include "MyString.h"

template <class T, const size_t N>

class MyStack 
{
private:

	T arr[N];
	size_t size;

public:

	MyStack(): size(0) {}

	void push(const T& element) 
	{

		if (size == N) throw std::logic_error("Full");
		else arr[size++] = element;

	}

	void push(T&& element)
	{

		if (size == N) throw std::logic_error("Full");
		else arr[size++] = std::move(element);

	}

	void pop() 
	{

		if(empty()) throw std::logic_error("Empty");
		size -= 1;

	}

	const T& top() const 
	{

		if (empty()) throw std::logic_error("Empty");
		return arr[size - 1];

	}

	bool empty() const 
	{

		return size == 0;

	}

	size_t getSize() const
	{

		return size;

	}

};

int main() 
{
    
    try 
    {

        MyStack<int, 5> intStack;
        
        for (int i = 1; i <= 5; i++)
        {

            intStack.push(i);
            std::cout << intStack.top() << ' ';
            
        }
        
        while (!intStack.empty()) 
        {

            std::cout << intStack.top() << ' ';
            intStack.pop();

        }
        
        intStack.pop();  

    }
    catch (const std::exception& e) 
    {

        std::cerr << "Int stack error: " << e.what() << std::endl << std::endl;

    }

    try
    {

        MyStack<MyString, 3> strStack;

        strStack.push(MyString("Hello"));      
        strStack.push(MyString("World"));      
        MyString exclamation = "!";
        strStack.push(exclamation);              

        while (!strStack.empty()) 
        {

            std::cout << strStack.top() << ' ';
            strStack.pop();

        }
        
        strStack.push("One");
        strStack.push("Two");
        strStack.push("Three");
        strStack.push("Overflow");  

    }
    catch (const std::exception& e) 
    {

        std::cerr << "String stack error: " << e.what() << std::endl;

    }

    return 0;

}
