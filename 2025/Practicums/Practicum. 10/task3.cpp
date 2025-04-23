#include "MyString.h"

class Student 
{
private:

	MyString name;
	unsigned fn = 0;
	unsigned course = 0;

public:

	Student(const MyString& name, unsigned fn, unsigned course): name(name), fn(fn), course(course) {}

	const MyString& getName() const 
	{

		return name;

	}

	unsigned getFn() const 
	{

		return fn;

	}

	unsigned getCoures() const
	{

		return course;

	}

	void print() const 
	{

		std::cout << name;
		std::cout << fn << " " << course;
		std::cout << std::endl;

	}

};

typedef bool (*predicate)(const Student* st1, const Student* st2);

typedef bool (*criteria)(const Student* st);

class StudentDB
{
private:

	Student** students = nullptr;
	int lastFreePosition = -1;
	int capacity = 8;
	int countOfStudents = 0;

	void copyFrom(const StudentDB& other) 
	{

		this->capacity = other.capacity;
		this->lastFreePosition = other.lastFreePosition;
		this->countOfStudents = other.countOfStudents;
		this->students = new Student * [other.capacity] {nullptr};

		for (int i = 0; i < capacity; i++)
		{

			if (other.students[i] != nullptr) 
			{

				this->students[i] = new Student(*other.students[i]);

			}

		}

	}

	void moveTo(StudentDB&& other) 
	{

		this->capacity = other.capacity;
		this->lastFreePosition = other.lastFreePosition;
		this->countOfStudents = other.countOfStudents;
		this->students = other.students;

		other.capacity = 0;
		other.lastFreePosition = -1;
		other.countOfStudents = 0;
		other.students = nullptr;

	}

	void free() 
	{
			
		for (int i = 0; i < capacity; i++)
		{

			if (students[i] != nullptr) 
			{

				delete students[i];
				students[i] = nullptr;

			}

		}

		delete[] students;
		students = nullptr;
		countOfStudents = 0;
		lastFreePosition = -1;
		capacity = 8;

	}

	void shiftLeft() 
	{

		Student** newStudents = new Student * [capacity] {nullptr};
		int currentIndex = 0;

		for (int i = 0; i < capacity; i++)
		{

			if (!students[i]) continue;

			newStudents[currentIndex] = students[i];
			students[i] = nullptr;
			currentIndex += 1;

		}

		delete[] students;
		students = newStudents;
		lastFreePosition = currentIndex;
		countOfStudents = currentIndex;

	}

	void resize(int newCapacity) 
	{

		if (newCapacity <= capacity) throw std::logic_error("Error");

		Student** newStudents = new Student * [newCapacity] {nullptr};

		for (int i = 0; i < capacity; i++)
		{

			newStudents[i] = students[i];
			students[i] = nullptr;

		}

		delete[] students;
		students = newStudents;
		capacity = newCapacity;

	}

	void updateLastFreePosition() 
	{

		for (int i = 0; i < capacity; i++)
		{

			if (!students[i]) 
			{

				lastFreePosition = i;
				return;

			}

		}

	}

public:

	StudentDB() 
	{

		countOfStudents = 0;
		capacity = 8;
		students = new Student * [capacity] {nullptr};
		lastFreePosition = 0;

	}

	StudentDB(const StudentDB& other) 
	{

		copyFrom(other);

	}

	StudentDB(StudentDB&& other) noexcept
	{

		moveTo(std::move(other));

	}

	StudentDB& operator = (const StudentDB& other) 
	{

		if (this != &other) 
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	StudentDB& operator = (StudentDB&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~StudentDB() 
	{

		free();

	}

	Student& operator [] (int index) 
	{

		if (index < 0 || index >= capacity) throw std::logic_error("Error");
		return *students[index];

	}

	const Student& operator [] (int index) const
	{

		if (index < 0 || index >= capacity || students[index] == nullptr) throw std::logic_error("Error");
		return *students[index];

	}

	void addStudent(const Student& st)
	{

		if (countOfStudents == capacity) resize(capacity * 2);

		students[lastFreePosition] = new Student(st);
		countOfStudents += 1;
		updateLastFreePosition();

	}

	void remove(int index) 
	{

		if (index < 0 || index >= capacity) throw std::logic_error("Error");

		delete students[index];
		students[index] = nullptr;
		updateLastFreePosition();

	}

	const Student& find(unsigned fn) const
	{

		for (int i = 0; i < capacity; i++)
		{

			if (!students[i]) continue;
			if (students[i]->getFn() == fn) return *students[i];

		}

		throw std::logic_error("Error");

	}

	int getCountOfStudents() const 
	{

		return countOfStudents;

	}

	int getCapacity() const
	{

		return capacity;

	}

	void display() const 
	{

		for (int i = 0; i < capacity; i++)
		{

			if (!students[i]) continue;
			students[i]->print();


		}

	}

	void sortBy(predicate function) 
	{

		shiftLeft();

		for (int i = 0; i < countOfStudents - 1; i++)
		{

			for (int j = 0; j < countOfStudents - i  -1; j++)
			{

				if (function(students[j], students[j + 1]))
				{

					std::swap(students[j], students[j + 1]);

				}

			}

		}

	}

};

class FilteredStudentDB: public StudentDB
{
public:

	void filter(criteria cr, const StudentDB& stD)
	{

		for (int i = 0; i < stD.getCapacity(); i++)
		{

			try
			{

				stD[i];

			}
			catch (const std::exception&)
			{

				continue;

			}

			if (cr(&stD[i])) 
			{

				addStudent(stD[i]);

			}

		}

	}

	void limit(int N, const StudentDB& stD) 
	{

		if (N > stD.getCapacity()) throw std::logic_error("Error");

		for (int i = 0; i < N; i++)
		{

			try
			{

				stD[i];

			}
			catch (const std::exception&)
			{

				continue;

			}

			addStudent(stD[i]);

		}

	}

};

bool pred1(const Student* st1, const Student* st2) 
{

	return st1->getFn() > st2->getFn();

}

bool cr1(const Student* st) 
{

	return st->getFn() > 50;

}

int main()
{

	Student st1("Yoan Baychev", 47, 1);
	Student st2("Ivailo Kunchev", 14, 1);
	Student st3("Kaloyan Markov", 67, 0);
	Student st4("Ilian Kunchev", 53, 2);
	Student st5("Nikola Topalov", 98, 1);

	Student st6("Yoan Baychev ve2", 47, 1);
	Student st7("Ivailo Kunchev ve2", 14, 1);
	Student st8("Kaloyan Markov ve2", 67, 0);
	Student st9("Ilian Kunchev ve2", 53, 2);
	Student st10("Nikola Topalov ve2", 98, 1);

	StudentDB db;
	db.addStudent(st1);
	db.addStudent(st2);
	db.addStudent(st3);
	db.addStudent(st4);
	db.addStudent(st5);
	db.display();
	std::cout << std::endl;

	db.remove(6);
	db.remove(2);
	db.remove(7);
	db.remove(1);
	db.display();
	std::cout << std::endl;

	db.addStudent(st6);
	db.addStudent(st7);
	db.addStudent(st8);
	db.addStudent(st9);
	db.addStudent(st10);
	db.display();
	std::cout << std::endl;

	const Student& found = db.find(47);
	found.print();
	std::cout << std::endl;

	db.sortBy(pred1);
	db.display();
	std::cout << std::endl;

	FilteredStudentDB fdb1;
	fdb1.filter(cr1, db);
	fdb1.display();
	std::cout << std::endl;

	FilteredStudentDB fdb2;
	fdb2.limit(2, db);
	fdb2.display();
	std::cout << std::endl;

	return 0;

}
