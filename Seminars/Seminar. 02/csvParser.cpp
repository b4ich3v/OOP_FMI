#include <iostream>
#include <sstream>
#include <fstream>
#include <assert.h>

const int FIELD_MAX_SIZE = 30;
const int MAX_FIELDS_ROW = 10;
const int ROWS_MAX_SIZE = 300;
const int BUFFER_SIZE = 1024;
const char SEP = ';';

typedef char Field[FIELD_MAX_SIZE];
typedef Field Row[MAX_FIELDS_ROW];

struct CsvTable
{

	Row rows[ROWS_MAX_SIZE];
	int rowsCount = 0;
	int collsCount = 0;

};

int parseRow(const char* row, Row& toReturn)
{

	std::stringstream ss(row);

	int currentColumnCount = 0;

	while (!ss.eof())
	{

		ss.getline(toReturn[currentColumnCount++], FIELD_MAX_SIZE, SEP);

	}

	return currentColumnCount;

}
CsvTable parseFromFile(std::istream& ifs)
{

	CsvTable result;
	char rowStr[BUFFER_SIZE];

	while (!ifs.eof())
	{

		ifs.getline(rowStr, BUFFER_SIZE, '\n');
		result.collsCount = parseRow(rowStr, result.rows[result.rowsCount++]);

	}

	return result;

}
CsvTable parseFromFile(const char* fileName)
{

	std::ifstream ifs(fileName);

	if (!ifs.is_open())
	{

		return {};

	}

	return parseFromFile(ifs);

}

void printTable(const CsvTable& table)
{

	for (int i = 0; i < table.rowsCount; i++)
	{

		for (int j = 0; j < table.collsCount; j++)
		{

			std::cout << table.rows[i][j] << "          ";

		}

		std::cout << std::endl;

	}

}

void saveRowToFile(std::ostream& ofs, const Row& row, size_t collsCount)
{

	for (int i = 0; i < collsCount; i++)
	{

		ofs << row[i];

		if (i != collsCount - 1)
		{

			ofs << SEP;

		}

	}

}

void saveToFile(std::ostream& ofs, const CsvTable& table)
{

	for (int i = 0; i < table.rowsCount; i++)
	{

		saveRowToFile(ofs, table.rows[i], table.collsCount);

		if (i != table.rowsCount - 1)
		{

			ofs << std::endl;

		}

	}

}

void saveToFile(const char* fileName, const CsvTable& table)
{

	std::ofstream ofs(fileName);
	saveToFile(ofs, table);
	ofs.close();

}

int getColumnIndex(const CsvTable& csvTable, const char* columnName)
{

	assert(csvTable.rowsCount >= 1);

	if (!columnName) 
	{

		return -1;

	}

	for (int i = 0; i < csvTable.collsCount; i++)
	{

		if (strcmp(csvTable.rows[0][i], columnName) == 0)
		{

			return i;

		}
			
	}

	return -1;

}

bool modify(CsvTable& csv, const char* columnName, const char* newValues, char sep)
{

	int columnIndex = getColumnIndex(csv, columnName);

	if (columnIndex < 0) 
	{

		return false;

	}

	std::stringstream ss(newValues);
	int rowIndex = 1;

	while (!ss.eof())
	{

		if (rowIndex > csv.rowsCount)
		{

			break;

		}

		ss.getline(csv.rows[rowIndex++][columnIndex], FIELD_MAX_SIZE, sep);

	}

	return true;

}

int main()
{

	CsvTable myFile = parseFromFile("students.csv");
	printTable(myFile);
	modify(myFile, "Ime", "Katerina|Petya", '|');
	saveToFile("students_new.csv", myFile);

	return 0;

}
