#include "MyString.h"
#include <fstream>
#include <iostream>
#include <sstream>
#pragma once

namespace HELPERS 
{

	int getFileSize(std::ifstream& file);

	int getCountOfSymbol(std::ifstream& file, const char ch);

	const char* cutWhiteSpaces(std::ifstream& file);

	void bubbleSort(int* data, int size);

}

class FileSorting
{
private:

	MyString fileName;
	int* data = nullptr;
	int size = 0;

	void free();

	void copyFrom(const FileSorting& other);

	void moveTo(FileSorting&& other);

public:

	FileSorting() = default;

	FileSorting(const MyString& fileName);

	FileSorting(const MyString& fileName, const int* data, int size);

	FileSorting(const FileSorting& other);

	FileSorting(FileSorting&& other) noexcept;

	FileSorting& operator = (const FileSorting& other);

	FileSorting& operator = (FileSorting&& other) noexcept;

	void clean();

	void setData(const int* data, int size);

	void setSize(int size);

	const MyString& getFileName() const;

	const int* getData() const;

	int getSize() const;

	virtual ~FileSorting();

	virtual void read() = 0;

	virtual void write() const = 0;

};

