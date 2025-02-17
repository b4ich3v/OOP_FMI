#include "CSVFileWriter.h"
#include <fstream>

CSVFileWriter::CSVFileWriter(const MyString& filePath): FileWriter(filePath){}

void CSVFileWriter::write(const int* arr, size_t size) const
{
	
	std::ofstream ofs(filePath.c_str());

	if (!ofs.is_open())
	{
		
		throw std::exception("Cannot open file");
		
	}

	for (int i = 0; i < size; i++)
	{
		
		ofs << arr[i];

		if (i != size - 1)
		{
			
			ofs << ',';
			
		}
		
	}

	ofs.close();
	
}
