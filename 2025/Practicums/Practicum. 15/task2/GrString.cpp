#include "GrString.h"

GrString::GrString():
	MyString() {}

GrString::GrString(const char* data):
	MyString(data) {}

GrString& GrString::operator += (const GrString& other) 
{

	char* newData = new char[getSize() + other.getSize() + 1];
	char* begPtr = newData;
	strncpy(newData, getData(), getSize());
	newData += getSize();
	strncpy(newData, other.getData(), other.getSize());
	newData = begPtr;
	newData[getSize() + other.getSize()] = '\0';

	*this = GrString(newData);
	delete[] newData;
	newData = nullptr;

	return *this;

}

GrString& GrString::operator /= (const GrString& other) 
{

	char resultBuffer[1024];
	size_t currentIndex = 0;

	for (int i = 0; i < getSize(); i++)
	{

		char currentSymbol = getData()[i];
		bool toBeAdded = true;

		for (int j = 0; j < other.getSize(); j++)
		{

			if (currentSymbol == other.getData()[j]) 
			{

				toBeAdded = false;
				break;

			}

		}

		if (toBeAdded) 
		{

			resultBuffer[currentIndex] = currentSymbol;
			currentIndex += 1;

		}

	}

	*this = GrString(resultBuffer);
	return *this;

}

bool GrString::operator == (const GrString& other) const 
{

	return strcmp(getData(), other.getData()) == 0;

}

GrString operator + (const GrString& left, const GrString& right) 
{

	GrString result(left);
	result += right;

	return result;

}

GrString operator / (const GrString& left, const GrString& right) 
{

	GrString result(left);
	result /= right;

	return result;

}

std::ostream& operator << (std::ostream& os, const GrString& other) 
{

	os << other.getData();
	return os;

}

std::istream& operator >> (std::istream& is, GrString& other) 
{

	char buffer[1024];
	is.getline(buffer, 1024, '\n');

	other = GrString(buffer);
	return is;

}
