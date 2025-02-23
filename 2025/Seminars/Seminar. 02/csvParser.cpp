#include <iostream>
#include <fstream>
#include <cstring>

enum class Major
{

	SI = 0,
	KN = 1,
	None = 2

};

struct Row
{
public:

	char firstName[100] = "None";
	char secondName[100] = "None";
	char email[100] = "fmi@gmail.com";
	char id[100] = "None";
	Major major = Major::None;

};

struct Table
{
public:

	Row* rows;

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

Row parseStudent(const char* data)
{

	if (!data) return {};

	Row result;
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

Row* readFromFile(std::ifstream& file, int& size)
{

	if (!file.is_open()) return {};

	size = getFileSize(file);
	Row* result = new Row[size];

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

void writeRow(std::ofstream& file, const Row& row)
{

	file << row.firstName << ",";
	file << row.secondName << ",";
	file << row.email << ",";
	file << row.id << ",";
	file << (int)row.major;
	file << std::endl;

}

void writeToFile(std::ofstream& file, const Table& table, int size)
{

	if (!table.rows || size <= 0 || !file.is_open()) return;

	for (int i = 0; i < size; i++)
	{

		writeRow(file, table.rows[i]);

	}

	file.close();

}

void printRow(const Row& row)
{

	std::cout << row.firstName << " ";
	std::cout << row.secondName << " ";
	std::cout << row.email << " ";
	std::cout << row.id << " ";

	switch (row.major)
	{

	case Major::SI: std::cout << "SI"; break;
	case Major::KN: std::cout << "Kn"; break;
	default: std::cout << "None"; break;

	}

	std::cout << std::endl;

}

void printRowById(const Table& table, int size, const char* id)
{

	for (int i = 0; i < size; i++)
	{

		if (!strcmp(table.rows[i].id, id))
		{

			printRow(table.rows[i]);

		}

	}

}

void changeEmail(const Table& table, int size, const char* id, const char* major, const char* newEmail)
{

	for (int i = 0; i < size; i++)
	{

		if (!strcmp(table.rows[i].id, id) &&
			(!strcmp("SI", major) && !(int)table.rows[i].major ||
			 !strcmp("KN", major) && (int)table.rows[i].major))
		{

			strncpy(table.rows[i].email, newEmail, strlen(newEmail));
			table.rows[i].email[strlen(newEmail)] = '\0';

		}

	}

}

int main()
{

	std::ifstream file1("../test1.txt");
	std::ofstream file2("../test2.txt");

	int size = 0;
	Table table;
	table.rows = readFromFile(file1, size);

	writeToFile(file2, table, size);
	changeEmail(table, size, "0MI0600328", "SI", "ludsum@gmail.com");
	printRowById(table, size, "0MI0600328");

	delete[] table.rows;
	return 0;

}
