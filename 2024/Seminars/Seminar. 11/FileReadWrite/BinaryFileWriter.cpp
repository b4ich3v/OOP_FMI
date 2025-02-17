#include "BinaryFileWriter.h"
#include <fstream>

BinaryFileWriter::BinaryFileWriter(const MyString& filePath): FileWriter(filePath){}

void BinaryFileWriter::write(const int* arr, size_t size) const
{
	
	std::ofstream ofs(filePath.c_str(), std::ios::binary);

	if (!ofs.is_open())
	{
		
		throw std::exception("Cannot open file");
		
	}

	ofs.write((const char*)arr, size * sizeof(int));
	ofs.close();
	
}
