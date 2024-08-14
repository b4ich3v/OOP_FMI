#include <iostream>
#include "uniquePtr.h"

void UniquePtr::free() 
{

	delete[] ptr;
	ptr = nullptr;

}

void UniquePtr::move(UniquePtr&& other)
{

	ptr = other.ptr;
	other.ptr = nullptr;

}

UniquePtr::UniquePtr()
{

	ptr = nullptr;

}

UniquePtr::UniquePtr(A* other)
{

	this->ptr = other;

}

UniquePtr::UniquePtr(UniquePtr&& other) noexcept 
{

	move(std::move(other));

}

UniquePtr& UniquePtr::operator = (UniquePtr&& other) noexcept 
{

	if (this != &other)
	{

		free();
		move(std::move(other));

	}

	return *this;

}

UniquePtr::~UniquePtr()
{

	free();

}

A& UniquePtr::operator * ()
{

	return *ptr;

}

const A& UniquePtr::operator * () const 
{

	return *ptr;

}

A* UniquePtr::operator -> () 
{

	return ptr;

}

const A* UniquePtr::operator -> () const
{

	return ptr;

}

A* UniquePtr::get() 
{

	return ptr;

}

void UniquePtr::reset(A* newPtr)
{

	free();
	ptr = newPtr;

}

A* UniquePtr::release()
{

	A* toReturn = ptr;
	ptr = nullptr;
	return toReturn;

}
