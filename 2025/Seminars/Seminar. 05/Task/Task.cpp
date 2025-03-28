#include "Task.h"

void Task::free() 
{

	delete[] description;
	description = nullptr;

	priority = 0;
	duration = 0;
	status = false;

}

void Task::setDescription(const char* description) 
{

	if (!description || this->description == description) throw std::logic_error("Error");

	delete[] this->description;
	this->description = new char[strlen(description) + 1];
	strncpy(this->description, description, strlen(description));
	this->description[strlen(description)] = '\0';

}

void Task::setDuration(int duration) 
{

	if (duration < 0) throw std::logic_error("Error");
	this->duration = duration;

}

void Task::setPriority(int priority) 
{

	if (priority < 0) throw std::logic_error("Error");
	this->priority = priority;

}

Task::Task(const char* description, int priority, int duration, const Time& startTime)
{

	setDescription(description);
	setPriority(priority);
	setDuration(duration);

	this->startTime = startTime;
	this->status = false;

}

void Task::readFromTxt(std::ifstream& file)
{

	int sizeOfDescription = 0;
	char buffer[CONSTANTS::MAX_SIZE_BUFFER];

	file >> sizeOfDescription;
	description = new char[sizeOfDescription + 1];
	file >> buffer;
	strncpy(description, buffer, sizeOfDescription);
	description[sizeOfDescription] = '\0';

	file >> priority;
	file >> status;
	file >> duration;

	char ch = 'a';
	file >> ch;
	int hours = 0;
	int minutes = 0;
	int seconds = 0;
	file >> hours;
	file >> minutes;
	file >> seconds;
	startTime = Time(hours, minutes, seconds);
	file >> ch;

}

Task::Task(std::ifstream& file) 
{

	readFromTxt(file);

}

void Task::writeToTxt(std::ofstream& file) const
{

	int sizeOfDescription = strlen(description);

	file << sizeOfDescription << " ";
	file << description << " ";
	file << priority << " ";
	file << status << " ";
	file << duration << " ";

	file << "(";
	file << startTime.getHours() << " ";
	file << startTime.getMinutes() << " ";
	file << startTime.getSeconds() << " ";
	file << ")";
	file << std::endl;

}

Task::~Task() 
{

	free();

}

const char* Task::getDescription() const 
{

	return description;

}

int Task::getDuration() const 
{

	return duration;

}

bool Task::getStatus() const 
{

	return status;

}

int Task::getPriority() const
{

	return priority;

}

void Task::setStatusTrue() 
{

	status = true;

}

Time Task::getStartTime() const 
{

	return startTime;

}

bool operator > (const Task& t1, const Task& t2) 
{

	if (t1.getPriority() == t2.getPriority()) 
	{

		Time time1 = t1.getStartTime();
		Time time2 = t2.getStartTime();

		int seconds1 = t1.getDuration() / HELPERS::SECONDS_IN_ONE_MINUTE;
		int seconds2 = t2.getDuration() / HELPERS::SECONDS_IN_ONE_MINUTE;

		for (int i = 0; i < seconds1; i++) time1.tick();

		for (int i = 0; i < seconds2; i++) time2.tick();

		return time1.compareByCondition(time2, 0);

	}

	return t1.getPriority() > t2.getPriority();

}

bool operator < (const Task& t1, const Task& t2)
{

	if (t1.getPriority() == t2.getPriority())
	{

		Time time1 = t1.getStartTime();
		Time time2 = t2.getStartTime();

		int seconds1 = t1.getDuration() / HELPERS::SECONDS_IN_ONE_MINUTE;
		int seconds2 = t2.getDuration() / HELPERS::SECONDS_IN_ONE_MINUTE;

		for (int i = 0; i < seconds1; i++) time1.tick();

		for (int i = 0; i < seconds2; i++) time2.tick();

		return time1.compareByCondition(time2, 1);

	}

	return t1.getPriority() < t2.getPriority();

}

bool operator >= (const Task& t1, const Task& t2) 
{

	return (t1 > t2) || (t1 == t2);

}

bool operator <= (const Task& t1, const Task& t2)
{

	return (t1 < t2) || (t1 == t2);

}

bool operator == (const Task& t1, const Task& t2) 
{

	return !((t1 < t2) && (t1 > t2));

}

bool operator != (const Task& t1, const Task& t2)
{

	return !(t1 == t2);

}

void Task::printTask() const 
{

	std::cout << description << " ";
	std::cout << priority << " ";
	std::cout <<  status << " ";
	std::cout << duration << " ";
	startTime.printTime();

}
