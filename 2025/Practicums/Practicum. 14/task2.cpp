#include <iostream>

template <class T>

class UniqePtr 
{
private:

	T* data = nullptr;

	void free() 
	{

		delete data;
		data = nullptr;

	}

	void moveTo(UniqePtr&& other)
	{

		data = other.data;
		other.data = nullptr;

	}

public:

	UniqePtr(const T* data) 
	{

		if (data == nullptr) throw std::logic_error("Error");
		this->data = new T(*data);

	}

	UniqePtr(T* data)
	{

		if (data == nullptr) throw std::logic_error("Error");
		this->data = new T(*data);

	}

	UniqePtr(const UniqePtr& other) = delete;

	UniqePtr& operator = (const UniqePtr& other) = delete;

	UniqePtr(UniqePtr&& other) noexcept 
	{

		moveTo(std::move(other));

	}

	UniqePtr& operator = (UniqePtr&& other) noexcept 
	{

		if (this != &other) 
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~UniqePtr() 
	{

		free();

	}

	const T* operator -> () const 
	{

		if (data == nullptr) throw std::logic_error("Error");
		return data;

	}

	T* operator -> () 
	{

		if (data == nullptr) throw std::logic_error("Error");
		return data;

	}

	const T& operator * () const
	{

		if (data == nullptr) throw std::logic_error("Error");
		return *data;

	}

	T& operator * () 
	{

		if (data == nullptr) throw std::logic_error("Error");
		return *data;

	}

};

struct Example 
{
public:

	Example() = default;

	void fictiveMethod() const 
	{

		std::cout << "OOP" << std::endl;

	}

};

int main() 
{

	UniqePtr<int> ptr1(new int(3));
	std::cout << *ptr1 << std::endl;

	char ch = 'a';
	char* ref = &ch;
	UniqePtr<char> ptr2(std::move(ref));
	std::cout << *ptr2 << std::endl;

	UniqePtr<Example> ptr3(new Example());
	ptr3->fictiveMethod();



	return 0;

}

