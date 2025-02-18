#include <iostream>

enum class Major
{

	SI,
	IS,
	KN,
	MA,
	None

};

struct Student
{
public:

	char name[33];
	int id;
	double avarageGrade;
	Major major;

};

typedef bool (*pred)(const Student&);

struct Course 
{
public:

	Student students[50];
	int countOfStudents;

};

Student creatStudent(const char* name, int id, Major major) 
{

	if (strlen(name) > 32) return {};

	Student result;
	strncpy(result.name, name, strlen(name));
	result.name[strlen(name)] = '\0';
	result.id = id;
	result.major = major;

	return result;

}

void printStudent(const Student& st) 
{

	std::cout << st.name << " " << st.id << " " << st.avarageGrade;

	switch (st.major)
	{

	case Major::SI: std::cout << "Si"; break;
	case Major::IS: std::cout << "IS"; break;
	case Major::KN: std::cout << "KN"; break;
	case Major::MA: std::cout << "Ma"; break;
	default: break;

	}

}

void addStudent(const Student& st, Course& course) 
{

	if (course.countOfStudents == 50) return;

	course.students[course.countOfStudents] = st;
	course.countOfStudents += 1;

}

void sortStudents(Course& course)
{

	for (int i = 0; i < course.countOfStudents; i++)
	{

		for (int j = 0; j < course.countOfStudents - i - 1; j++)
		{

			if ((course.students[j].avarageGrade < course.students[j + 1].avarageGrade) ||
				(strcmp(course.students[j].name, course.students[j + 1].name) > 0 &&
				 course.students[j].avarageGrade == course.students[j + 1].avarageGrade))
			{

				std::swap(course.students[j], course.students[j + 1]);

			}

		}

	}

}

void filter(const Course& course, pred f)
{

	for (int i = 0; i < course.countOfStudents; i++)
	{

		if (f(course.students[i]))
		{

			printStudent(course.students[i]);

		}

	}

}
