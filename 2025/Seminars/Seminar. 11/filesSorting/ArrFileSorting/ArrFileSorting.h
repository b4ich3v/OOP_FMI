#include "FileSorting.h"
#pragma once

class ArrFileSorting: public FileSorting
{
public:

	ArrFileSorting(const MyString& fileName);

	ArrFileSorting(const MyString& fileName, const int* data, int size);

	void read() override;

	void write() const override;

};

