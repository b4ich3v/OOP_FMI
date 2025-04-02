#include <iostream>
#include <cstring>
#pragma once

class Song
{
private:

	char* name = nullptr;
	char* contractor = nullptr;
	double duration = 0;

	void free();

	void copyFrom(const Song& other);

public:

	Song() = default;

	Song(const char* name, const char* contractor, double duration);

	Song(const Song& other);

	Song& operator = (const Song& other);

	~Song();

	double getDuration() const;

	const char* getName() const;

	const char* getContractor() const;

	friend std::ostream& operator << (std::ostream& os, const Song& song);

	friend std::istream& operator >> (std::istream& os, Song& song);

};
