#include "FileSorting.h"

void FileSorting::free() 
{

	delete[] data;
	data = nullptr;
	size = 0;

}

void FileSorting::copyFrom(const FileSorting& other) 
{

	this->fileName = other.fileName;
	this->data = new int[other.size];
	this->size = other.size;

	for (int i = 0; i < size; i++)
	{

		this->data[i] = other.data[i];

	}

}

void FileSorting::moveTo(FileSorting&& other) 
{

	this->fileName = other.fileName;
	this->data = other.data;
	this->size = other.size;

	other.fileName = "default";
	other.data = nullptr;
	other.size = 0;

}

FileSorting::FileSorting(const MyString& fileName, const int* data, int size) 
{

	if (!data || size < 0) throw std::logic_error("Error");

	this->fileName = fileName;
	this->data = new int[size];
	this->size = size;

	for (int i = 0; i < size; i++)
	{

		this->data[i] = data[i];

	}

	HELPERS::bubbleSort(this->data, this->size);

}

FileSorting::FileSorting(const MyString& fileName) 
{

	this->fileName = fileName;
	this->data = nullptr;
	this->size = 0;

}

FileSorting::FileSorting(const FileSorting& other) 
{

	copyFrom(other);

}

FileSorting::FileSorting(FileSorting&& other) noexcept 
{

	moveTo(std::move(other));

}

FileSorting& FileSorting::operator = (const FileSorting& other)
{

	if (this != &other) 
	{

		free();
		copyFrom(other);

	}

	return *this;

}

FileSorting& FileSorting::operator = (FileSorting&& other) noexcept
{

	if (this != &other)
	{

		free();
		moveTo(std::move(other));

	}

	return *this;

}

FileSorting::~FileSorting() 
{

	free();

}

int HELPERS::getFileSize(std::ifstream& file) 
{

	int currentPosition = file.tellg();
	file.seekg(0, std::ios::end);
	int result = file.tellg();

	file.clear();
	file.seekg(currentPosition);

	return result;

}

const char* HELPERS::cutWhiteSpaces(std::ifstream& file)
{
	
	file.clear();
	file.seekg(0, std::ios::beg);

	int size = getFileSize(file);
	char* buffer = new char[size + 1];
	file.read(buffer, size);
	buffer[size] = '\0';

	char* out = new char[size + 1];
	int currentIndex = 0;

	for (int i = 0; buffer[i] != '\0'; i++) 
	{
		char c = buffer[i];

		if (c != ' ' && c != '\n' && c != '\t' && c != '\r')
			out[currentIndex++] = c;
	}

	out[currentIndex] = '\0';

	delete[] buffer;
	return out;  

}

void HELPERS::bubbleSort(int* data, int size) 
{

	for (int i = 0; i < size - 1; i++)
	{

		for (int j = 0; j < size - i - 1; j++)
		{

			if (data[j] > data[j + 1]) std::swap(data[j], data[j + 1]);

		}

	}

}

int HELPERS::getCountOfSymbol(std::ifstream& file, const char ch) 
{

	int currentPosition = file.tellg();
	file.seekg(0, std::ios::end);

	int result = 0;
	char c = 'a';

	while (file.get(c)) 
	{

		if (c == ch) result += 1;

	}

	file.clear();
	file.seekg(currentPosition);

	return result;

}

void FileSorting::clean() 
{

	free();

}

void FileSorting::setData(const int* data, int size) 
{

	this->data = new int[size];
	setSize(size);

	for (int i = 0; i < size; i++)
	{

		this->data[i] = data[i];

	}

	HELPERS::bubbleSort(this->data, this->size);

}

void FileSorting::setSize(int size) 
{

	this->size = size;

}

const MyString& FileSorting::getFileName() const 
{

	return fileName;

}

const int* FileSorting::getData() const
{

	return data;

}

int FileSorting::getSize() const 
{

	return size;

}
