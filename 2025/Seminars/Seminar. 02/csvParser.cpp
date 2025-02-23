#include <iostream>
#include <fstream>
#include <cstring>

const int MAX_COUNT = 100;
typedef char Field[MAX_COUNT];

enum class Major
{

	SI = 0,
	KN = 1,
	None = 2

};

struct Row
{
public:

	Field fields[4];
	Major major = Major::None;

};

struct Table
{
public:

	Row* rows;
	int countOfRows;

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

			strncpy(result.fields[0], helper, counter);
			result.fields[0][counter] = '\0';
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

			strncpy(result.fields[1], helper, counter);
			result.fields[1][counter] = '\0';
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

			strncpy(result.fields[2], helper, counter);
			result.fields[2][counter] = '\0';
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

			strncpy(result.fields[3], helper, counter);
			result.fields[3][counter] = '\0';
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

	file << row.fields[0] << ",";
	file << row.fields[1] << ",";
	file << row.fields[2] << ",";
	file << row.fields[3] << ",";
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

	std::cout << row.fields[0] << " ";
	std::cout << row.fields[1] << " ";
	std::cout << row.fields[2] << " ";
	std::cout << row.fields[3] << " ";

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

		if (!strcmp(table.rows[i].fields[3], id))
		{

			printRow(table.rows[i]);

		}

	}

}

void changeEmail(const Table& table, int size, const char* id, const char* major, const char* newEmail)
{

	for (int i = 0; i < size; i++)
	{

		if (!strcmp(table.rows[i].fields[3], id) &&
			(!strcmp("SI", major) && !(int)table.rows[i].major ||
				!strcmp("KN", major) && (int)table.rows[i].major))
		{

			strncpy(table.rows[i].fields[2], newEmail, strlen(newEmail));
			table.rows[i].fields[2][strlen(newEmail)] = '\0';

		}

	}

}

int main()
{

	std::ifstream file1("../test1.txt");
	std::ofstream file2("../test2.txt");

	Table table;
	table.rows = readFromFile(file1, table.countOfRows);

	writeToFile(file2, table, table.countOfRows);
	changeEmail(table, table.countOfRows, "0MI0600328", "SI", "ludsum@gmail.com");
	printRowById(table, table.countOfRows, "0MI0600328");

	delete[] table.rows;
	return 0;

}
