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

	char firstName[100] = "None";
	char secondName[100] = "None";
	char email[100] = "fmi@gmail.com";
	char id[100] = "None";
	Major major = Major::None;

};

int getFileSize(std::ifstream& file)
{

	int counter = 0;
	char buffer[1024];

	while (true)
	{

		file.getline(buffer, 1024);
		counter += 1;

		if (file.eof()) break;

	}

	file.clear();
	file.seekg(0, std::ios::beg);
	return counter;

}

Student parseStudent(const char* data)
{

	if (!data) return {};

	Student result;
	int counter = 0;
	const char* helper = data;

	while (*data != '\0')
	{

		if (*data == ',')
		{

			strncpy(result.firstName, helper, counter);
			result.firstName[counter] = '\0';
			break;

		}

		counter += 1;
		data += 1;

	}

	counter = 0;
	data += 1;
	helper = data;

	while (*data != '\0')
	{

		if (*data == ',')
		{

			strncpy(result.secondName, helper, counter);
			result.secondName[counter] = '\0';
			break;

		}

		counter += 1;
		data += 1;

	}

	counter = 0;
	data += 1;
	helper = data;

	while (*data != '\0')
	{

		if (*data == ',')
		{

			strncpy(result.email, helper, counter);
			result.email[counter] = '\0';
			break;

		}

		counter += 1;
		data += 1;

	}

	counter = 0;
	data += 1;
	helper = data;

	while (*data != '\0')
	{

		if (*data == ',')
		{

			strncpy(result.id, helper, counter);
			result.id[counter] = '\0';
			break;

		}

		counter += 1;
		data += 1;

	}

	data += 1;

	switch (*data)
	{

	case '0': result.major = Major::SI; break;
	case '1': result.major = Major::KN; break;
	default: result.major = Major::None; break;

	}

	return result;

}

Student* readFromFile(std::ifstream& file, int& size)
{

	if (!file.is_open()) return {};

	size = getFileSize(file);
	Student* result = new Student[size];

	char buffer[1024];
	int currentIndex = 0;

	while (true)
	{

		file.getline(buffer, 1024);
		result[currentIndex] = parseStudent(buffer);
		currentIndex += 1;

		if (file.eof()) break;

	}

	file.close();
	return result;

}

void writeStudent(std::ofstream& file, Student st)
{

	file << st.firstName << ",";
	file << st.secondName << ",";
	file << st.email << ",";
	file << st.id << ",";
	file << (int)st.major;
	file << std::endl;

}

void writeToFile(std::ofstream& file, Student* students, int size)
{

	if (!students || size <= 0 || !file.is_open()) return;

	for (int i = 0; i < size; i++)
	{

		writeStudent(file, students[i]);

	}

	file.close();

}

void printStudent(const Student& st)
{

	std::cout << st.firstName << " ";
	std::cout << st.secondName << " ";
	std::cout << st.email << " ";
	std::cout << st.id << " ";

	switch (st.major)
	{

	case Major::SI: std::cout << "SI"; break;
	case Major::KN: std::cout << "Kn"; break;
	default: std::cout << "None"; break;

	}

	std::cout << std::endl;

}

void printStudentById(Student* students, int size, const char* id)
{

	for (int i = 0; i < size; i++)
	{

		if (!strcmp(students[i].id, id))
		{

			printStudent(students[i]);

		}

	}

}

void changeEmail(Student* students, int size, const char* id, const char* major, const char* newEmail)
{

	for (int i = 0; i < size; i++)
	{

		if (!strcmp(students[i].id, id) &&
			(!strcmp("SI", major) && !(int)students[i].major ||
			 !strcmp("KN", major) && (int)students[i].major))
		{

			strncpy(students[i].email, newEmail, strlen(newEmail));
			students[i].email[strlen(newEmail)] = '/0';

		}

	}

}

int main()
{

	std::ifstream file1("../test1.txt");
	std::ofstream file2("../test2.txt");

	int size = 0;
	Student* students = readFromFile(file1, size);

	writeToFile(file2, students, size);
	changeEmail(students, size, "0MI0600328", "SI", "ludsum@gmail.com");
	printStudentById(students, size, "0MI0600328");

	delete[] students;
	return 0;

}
