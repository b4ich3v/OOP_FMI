#include <iostream>
#include <fstream>
#include <cstring>

enum class Major
{

	SI = 0,
	KN = 1,
	None = 2

};

struct Student
{
public:

	char name[50] = "Default";
	int grades[100] {};
	int countOfGrades = 0;
	Major major = Major::None;

};

int getCountOfLines(std::ifstream& file)
{

	int counter = 0;
	char buffer[1024];

	while (true)
	{

		file.getline(buffer, 1024);
		counter += 1;

		if (file.eof()) break;

	}

	file.seekg(0, std::ios::beg);
	file.clear();

	return counter;

}

void saveStudentToFile(const Student& st, std::ofstream& file)
{

	file << st.name << " ";
	file << st.countOfGrades << " ";

	for (int i = 0; i < st.countOfGrades; i++)
	{

		file << st.grades[i] << " ";

	}

	file << (int)st.major;
	file << '\n';

}

void readStudentFromFile(Student& st, std::ifstream& file)
{

	char buffer[50];
	file >> buffer;

	strncpy(st.name, buffer, 50);
	st.name[strlen(buffer)] = '\0';

	file >> st.countOfGrades;

	for (int i = 0; i < st.countOfGrades; i++)
	{

		file >> st.grades[i];

	}

	int majorNumber = 0;
	file >> majorNumber;

	switch (majorNumber)
	{

	case 0: st.major = Major::SI; break;
	case 1: st.major = Major::KN; break;
	default:  st.major = Major::None; break;

	}

}

void writeStudentArrayToFile(const char* fileName, const Student* students, int size)
{

	std::ofstream file(fileName);

	if (!file.is_open()) return;

	for (int i = 0; i < size; i++)
	{

		saveStudentToFile(students[i], file);

	}

	file.close();

}

Student* readStudentArrayFromFile(const char* fileName, int& size)
{

	std::ifstream file(fileName);

	if (!file.is_open()) return nullptr;

	size = getCountOfLines(file);
	Student* result = new Student[size];

	for (int i = 0; i < size; i++)
	{

		readStudentFromFile(result[i], file);

	}

	return result;

}

void printStudents(Student* students, int size)
{

	for (int i = 0; i < size; i++)
	{

		std::cout << students[i].name << " ";
		std::cout << students[i].countOfGrades << " ";

		for (int j = 0; j < students[i].countOfGrades; j++)
		{

			std::cout << students[i].grades[j] << " ";

		}

		switch (students[i].major)
		{

		case Major::SI: std::cout << "SI"; break;
		case Major::KN: std::cout << "KN"; break;
		default: std::cout << "None"; break;

		}

		std::cout << std::endl;

	}

}

int main()
{

	/*Student students[3] =
	{

		{"Yoan", {6, 6, 6}, 3, Major::SI},
		{"Ilian", {2, 2, 3}, 3, Major::SI},
		{"Koki", {2, 2, 2}, 3, Major::KN}

	};

	writeStudentArrayToFile("../test1.txt", students, 3);*/

	int size = 0;
	Student* students = readStudentArrayFromFile("../test1.txt", size);
	printStudents(students, size);

	delete[] students;
	return 0;

}
