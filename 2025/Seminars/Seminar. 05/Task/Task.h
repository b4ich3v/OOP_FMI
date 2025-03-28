#include <iostream>
#include <fstream>
#include <cstring>
#include "Time.h"
#pragma once

namespace CONSTANTS
{

	const int MAX_SIZE_BUFFER = 1024;

}

class Task
{
private:

	char* description = nullptr;
	int priority = 0;
	bool status = false;
	int duration = 0;

	Time startTime;

	void free();

	void copyFrom(const Task& other);

	void setDescription(const char* description);

	void setDuration(int duration);

	void setPriority(int priority);

public:

	Task() = default;

	Task(const char* description, int priority, int duration, const Time& startTime);

	Task(std::ifstream& file);

	Task(const Task& other);

	Task& operator = (const Task& other) = delete;

	~Task();

	const char* getDescription() const;

	int getPriority() const;

	int getDuration() const;

	bool getStatus() const;

	void setStatusTrue();

	void writeToTxt(std::ofstream& file) const;

	void readFromTxt(std::ifstream& file);

	Time getStartTime() const;

	void printTask() const;

};

bool operator >= (const Task& t1, const Task& t2);

bool operator <= (const Task& t1, const Task& t2);

bool operator > (const Task& t1, const Task& t2);

bool operator < (const Task& t1, const Task& t2);

bool operator == (const Task& t1, const Task& t2);

bool operator != (const Task& t1, const Task& t2);
