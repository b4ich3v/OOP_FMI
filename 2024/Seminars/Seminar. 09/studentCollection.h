#inlcude <iostream>
#include "studentExample.h"

class StudentCollection
{
private:

	Student** data;
	int size;
	int capacity;

	void free();

	void copyFrom(const StudentCollection& other);

	void move(StudentCollection&& other);

	void resize(int newCapacity);

	int getFirstFreeIndex() const;

public:

	StudentCollection();

	StudentCollection(const StudentCollection& other);

	StudentCollection& operator = (const StudentCollection& other);

	void pushAt(int index, const Student& other);

	void pushAt(int index, Student&& other);

	void push(const Student& other);

	void push(Student&& other);

	void removeAt(int index);

	bool contains(int index) const;

	int getSize() const;

	int getCapacity() const;

	const Student& at(int index) const;

	StudentCollection& operator = (StudentCollection&& other) noexcept;

	StudentCollection(StudentCollection&& other) noexcept;

	~StudentCollection();

};
