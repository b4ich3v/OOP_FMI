#include "FileSorting.h"
#pragma once

class BinaryFileSorting: public FileSorting
{
public:

	BinaryFileSorting(const MyString& fileName);

	BinaryFileSorting(const MyString& fileName, const int* data, int size);

	void read() override;

	void write() const override;

};

