#include <iostream>

enum class Age : uint8_t
{

	freshman,
	sophomore,
	junior,
	senior,
	none

};

struct Student
{
public:

	char* name = nullptr;
	char* egn = nullptr;
	Age age;

	void copyFrom(const Student& other) 
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));

		this->egn = new char[strlen(other.egn) + 1];
		strncpy(this->egn, other.egn, strlen(other.egn));

		this->age = other.age;

	}

	void moveTo(Student&& other) 
	{

		name = other.name;
		egn = other.egn;
		age = other.age;

		other.name = nullptr;
		other.egn = nullptr;
		other.age = Age::none;

	}

	void free() 
	{

		delete[] name;
		delete[] egn;
		age = Age::none;

	}

	Student() : name(nullptr), egn(nullptr) 
	{

		age = Age::none;

	}

	Student(const Student& other)
	{

		copyFrom(other);

	}

	Student(Student&& other) noexcept
	{

		moveTo(std::move(other));

	}

	Student& operator = (const Student& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	Student& operator = (Student&& other) noexcept
	{

		if (this != &other)
		{

			free();
			moveTo(std::move(other));

		}

		return *this;

	}

	~Student()
	{

		free();

	}

};

Student readStudent(const char* name, const char* egn, Age age)
{

	Student result;

	result.name = new char[strlen(name) + 1];
	strncpy(result.name, name, strlen(name));

	result.egn = new char[strlen(egn) + 1];
	strncpy(result.egn, egn, strlen(egn));

	result.age = age;

	return result;

}

void printStudent(const Student& st)
{

	std::cout << st.name << " " << st.egn << " ";

	switch (st.age)
	{

	case Age::freshman: std::cout << "freshman"; break;
	case Age::junior: std::cout << "junior"; break;
	case Age::senior: std::cout << "senior"; break;
	case Age::sophomore: std::cout << "sophomore"; break;
	default: break;

	}

}

struct University
{
public:

	Student* students = nullptr;
	int size;

	bool hasStudent(const Student& st) const
	{

		for (int i = 0; i < size; i++)
		{

			if (!strcmp(st.egn, students[i].egn))
			{

				return true;

			}

		}

		return false;

	}

	void addStudenty(const Student& st)
	{

		if (hasStudent(st)) return;

		students[size] = st;
		size += 1;

	}

	void removeStudent(const char* egn)
	{

		if (size == 0) return;

		int index = 0;

		for (int i = 0; i < size; i++)
		{

			if (!strcmp(egn, students[i].egn))
			{

				index = i;
				break;

			}

		}

		for (int i = index; i < size - 1; i++)
		{

			students[i] = students[i + 1];

		}

		size -= 1;

	}

	void printStudents(Age age)
	{

		for (int i = 0; i < size; i++)
		{

			if ((int)students[i].age == (int)age)
			{

				printStudent(students[i]);
				std::cout << std::endl;

			}

		}

	}

};
