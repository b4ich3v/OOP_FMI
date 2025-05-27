#include <iostream>

template <class T>

class SharedPtr 
{
private:

	T* data = nullptr;
	size_t* refCounter = nullptr;

	void free() 
	{

		(*refCounter) -= 1;

		if (*refCounter == 0) 
		{

			delete data;
			delete refCounter;
			data = nullptr;
			refCounter = nullptr;

		}

	}

	void copyFrom(const SharedPtr& other) 
	{

		data = other.data;
		refCounter = other.refCounter;

		if (refCounter != nullptr) 
		{

			(*refCounter) += 1l;

		}

	}

	void moveTo(SharedPtr&& other) 
	{

		data = other.data;
		refCounter = other.refCounter;

		other.data = nullptr;
		other.refCounter = nullptr;

	}

public:

	SharedPtr(const T* data)
	{

		this->data = new T(*data);
		this->refCounter = new size_t(1);

	}

	SharedPtr(T* data)
	{

		this->data = new T(*data);
		this->refCounter = new size_t(1);

	}

	SharedPtr(const SharedPtr& other) 
	{

		copyFrom(other);

	}

	SharedPtr(SharedPtr&& other) noexcept 
	{

		moveTo(std::move(other));

	}

	SharedPtr& operator = (const SharedPtr& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	SharedPtr& operator = (SharedPtr&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~SharedPtr() 
	{

		free();

	}

	const T& operator * () const 
	{

		if (data != nullptr) return *data;

	}

	T& operator * ()
	{

		if (data != nullptr) return *data;

	}

	const T* operator -> () const
	{

		if (data != nullptr) return data;

	}

	T* operator -> ()
	{

		if (data != nullptr) return data;

	}

	operator bool() const
	{

		return data != nullptr;

	}

	void reset(const T* data = nullptr) 
	{

		if (data == nullptr) free();
		else *this = SharedPtr(data);

	}

	size_t getRefCount() const 
	{

		if (refCounter == nullptr) throw std::logic_error("Error");
		return *refCounter;

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

	SharedPtr<int> ptr1(new int(47));
	SharedPtr<int> ptr2 = ptr1;
	SharedPtr<int> ptr3 = ptr1;
	SharedPtr<int> ptr4 = ptr1;

	std::cout << ptr1.getRefCount() << " " << ptr2.getRefCount() << " "
		<< ptr3.getRefCount() << " " << ptr4.getRefCount() << std::endl;

	std::cout << *ptr1 << std::endl;
	std::cout << *ptr2 << std::endl;
	std::cout << *ptr3 << std::endl;
	std::cout << *ptr4 << std::endl;

	SharedPtr<Example> ptr(new Example());
	ptr->fictiveMethod();

	return 0;

}

