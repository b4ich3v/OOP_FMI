#include <iostream>
#pragma 

template <class T>

class SharedPtr
{
private:

	T* data = nullptr;
	size_t* refCounter = nullptr;

	void free();

	void copyFrom(const SharedPtr& other);

	void moveTo(SharedPtr&& other);

public:

	SharedPtr(const T* data);

	SharedPtr(T* data);

	SharedPtr(const SharedPtr& other);

	SharedPtr(SharedPtr&& other) noexcept;

	SharedPtr& operator = (const SharedPtr& other);

	SharedPtr& operator = (SharedPtr&& other) noexcept;

	~SharedPtr();

	const T* operator -> () const;

	T* operator -> ();

	const T& operator * () const;

	T& operator * ();

	size_t getRefCount() const;

	void reset(const T* ptr = nullptr);

};

template <class T>

SharedPtr<T>::SharedPtr(const T* data)
{

	if (!data) throw std::logic_error("Error");
	this->data = new T(*data);
	this->refCounter = new size_t(1);

}

template <class T>

SharedPtr<T>::SharedPtr(T* data) 
{

	if (!data) throw std::logic_error("Error");
	this->data = new T(*data);
	this->refCounter = new size_t(1);

}

template <class T>

SharedPtr<T>::SharedPtr(const SharedPtr& other) 
{

	copyFrom(other);

}

template <class T>

SharedPtr<T>::SharedPtr(SharedPtr&& other) noexcept 
{

	moveTo(std::move(other));

}

template <class T>

SharedPtr<T>& SharedPtr<T>::operator = (const SharedPtr<T>& other) 
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

template <class T>

SharedPtr<T>& SharedPtr<T>::operator = (SharedPtr<T>&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

template <class T>

SharedPtr<T>::~SharedPtr() 
{

	free();

}

template <class T>

const T* SharedPtr<T>::operator -> () const 
{

	if (!data) throw std::logic_error("Error");
	return data;

}

template <class T>

T* SharedPtr<T>::operator -> ()
{

	if (!data) throw std::logic_error("Error");
	return data;

}

template <class T>

const T& SharedPtr<T>::operator * () const 
{

	if (!data) throw std::logic_error("Error");
	return *data;

}

template <class T>

T& SharedPtr<T>::operator * ()
{

	if (!data) throw std::logic_error("Error");
	return *data;

}

template <class T>

size_t SharedPtr<T>::getRefCount() const 
{

	if (!refCounter) throw std::logic_error("Error");
	return *refCounter;

}

template <class T>

void SharedPtr<T>::reset(const T* ptr) 
{

	free();

	if(ptr != nullptr)
	{

		data = new T(*ptr);
		(*refCounter) = 1;

	}

}

template <class T>

void SharedPtr<T>::free() 
{

	if (!refCounter && !data) return;

	(*refCounter) -= 1;

	if ((*refCounter) == 0) 
	{

		delete data;
		delete refCounter;
		data = nullptr;
		refCounter = nullptr;

	}

}

template <class T>

void SharedPtr<T>::copyFrom(const SharedPtr& other) 
{

	data = other.data;
	refCounter = other.refCounter;

	(*refCounter) += 1;

}

template <class T>

void SharedPtr<T>::moveTo(SharedPtr&& other) 
{

	data = other.data;
	refCounter = other.refCounter;

	other.data = nullptr;
	other.refCounter = nullptr;

}
