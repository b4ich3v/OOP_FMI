#include "FileSorting.h"
#pragma once

class CsvFileSorting: public FileSorting
{
public:

	CsvFileSorting(const MyString& fileName);

	CsvFileSorting(const MyString& fileName, const int* data, int size);

	void read() override;

	void write() const override;

};

