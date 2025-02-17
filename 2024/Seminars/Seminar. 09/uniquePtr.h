#pragma once

class UniquePtr 
{
private:

	A* ptr;

	void free();

	void move(UniquePtr&& other);

public:

	UniquePtr();

	UniquePtr(A* other);

	UniquePtr(const UniquePtr& other) = delete;

	UniquePtr(UniquePtr&& other) noexcept;

	UniquePtr& operator = (UniquePtr&& other) noexcept;

	UniquePtr& operator = (const UniquePtr& other) = delete;

	~UniquePtr();

	A& operator * ();

	const A& operator * () const;

	A* operator -> ();

	const A* operator -> () const;

	A* get();

	void reset(A* newPtr);

	A* release();

};
