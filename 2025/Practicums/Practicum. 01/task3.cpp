#include <iostream>

enum class Age: uint8_t 
{

	freshman,
	sophomore,
	junior,
	senior

};

struct Student
{
public:

	char* name = nullptr;
	char* egn = nullptr;
	Age age;

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
