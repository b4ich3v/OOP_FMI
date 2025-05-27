#include <iostream>
#pragma

class CommunicationPipe
{
private:

	size_t countOfSharedPtrs = 0;
	size_t countOfWeakPtrs = 0;

public:

	void addSharedPtr()
	{

		countOfSharedPtrs += 1;
		if (countOfSharedPtrs == 1) countOfWeakPtrs += 1;

	}

	void removeSharedPtr()
	{

		countOfSharedPtrs -= 1;
		if (countOfSharedPtrs == 0) countOfWeakPtrs -= 1;

	}

	void addWeakPtr()
	{

		countOfWeakPtrs += 1;

	}

	void removeWeakPtr()
	{

		countOfWeakPtrs -= 1;

	}

	bool noOwners() const
	{

		return countOfSharedPtrs == 0;

	}

	bool noVisitors() const
	{

		return countOfWeakPtrs == 0;

	}

	size_t getCountOfSharedPtrs() const
	{

		return countOfSharedPtrs;

	}

	size_t getCountOfWeakPtrs() const
	{

		return countOfWeakPtrs;

	}

};

class WeakPtr;

template <class T>

class SharedPtr
{
private:

	T* data = nullptr;
	CommunicationPipe* pipe = nullptr;

	void free();

	void copyFrom(const SharedPtr& other);

	void moveTo(SharedPtr&& other);

public:

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

	void reset(T* ptr = nullptr);

	friend class WeakPtr;

};

template <class T>

SharedPtr<T>::SharedPtr(T* data): data(data)
{

	if (!data) throw std::logic_error("Error");
	this->pipe = new CommunicationPipe();
	this->pipe->addSharedPtr();

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

	if (!pipe) throw std::logic_error("Error");
	return pipe->getCountOfSharedPtrs();

}

template <class T>

void SharedPtr<T>::reset(T* ptr)
{

	free();

	if(ptr != nullptr)
	{

		data = ptr;
		pipe = new CommunicationPipe();
		pipe->addSharedPtr();

	}

}

template <class T>

void SharedPtr<T>::free()
{

	if (!data) return;

	pipe->removeSharedPtr();

	if (pipe->noOwners())
	{

		delete data;
		data = nullptr;

		if (pipe->noVisitors())
		{

			delete pipe;
			pipe = nullptr;

		}

	}

}

template <class T>

void SharedPtr<T>::copyFrom(const SharedPtr& other)
{

	data = other.data;
	pipe = other.pipe;
	if (pipe) pipe->addSharedPtr();

}

template <class T>

void SharedPtr<T>::moveTo(SharedPtr&& other)
{

	data = other.data;
	pipe = other.pipe;

	other.data = nullptr;
	other.pipe = nullptr;

}

