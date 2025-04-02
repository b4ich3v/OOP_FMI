#include "Song.h"

void Song::free()
{

	delete[] name;
	name = nullptr;

	delete[] contractor;
	contractor = nullptr;

	duration = 0;

}

void Song::copyFrom(const Song& other) 
{

	this->name = new char[strlen(other.name) + 1];
	strncpy(this->name, other.name, strlen(other.name));
	this->name[strlen(other.name)] = '\0';

	this->contractor = new char[strlen(other.contractor) + 1];
	strncpy(this->contractor, other.contractor, strlen(other.contractor));
	this->contractor[strlen(other.contractor)] = '\0';

	this->duration = other.duration;

}

Song::Song(const char* name, const char* contractor, double duration) 
{

	if (!name || !contractor || duration < 0) throw std::logic_error("Error");

	this->name = new char[strlen(name) + 1];
	strncpy(this->name, name, strlen(name));
	this->name[strlen(name)] = '\0';

	this->contractor = new char[strlen(contractor) + 1];
	strncpy(this->contractor, contractor, strlen(contractor));
	this->contractor[strlen(contractor)] = '\0';

	this->duration = duration;

}

Song::Song(const Song& other)
{
	
	copyFrom(other);

}

Song& Song::operator = (const Song& other) 
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Song::~Song()
{

	free();
	
}

double Song::getDuration() const 
{

	return duration;

}

const char* Song::getName() const 
{

	return name;

}

const char* Song::getContractor() const 
{

	return contractor;

}

std::ostream& operator << (std::ostream& os, const Song& song) 
{

	os << song.getName() << std::endl;
	os << song.getContractor() << std::endl;
	os << song.getDuration() << std::endl;

	return os;

}

std::istream& operator >> (std::istream& is, Song& song) 
{

	char buffer[1024];
	double newDuration = 0;

	is.getline(buffer, 1024);
	is.getline(buffer, 1024);
	is >> newDuration;
	is.ignore(1);

	char* newData = new char[strlen(buffer) +1];
	strncpy(newData, buffer, strlen(buffer));
	newData[strlen(buffer)] = '\0';

	char* newContractor = new char[strlen(buffer) + 1];
	strncpy(newContractor, buffer, strlen(buffer));
	newContractor[strlen(buffer)] = '\0';

	Song newSong(newData, newContractor, newDuration);
	song = newSong;

	delete[] newData;
	delete[] newContractor;
	newData = nullptr;
	newContractor = nullptr;

	return is;

}

void Song::writeToBinary(std::ofstream& file) const 
{

	int sizeOfName = strlen(name);
	int sizeOfContractor = strlen(contractor);

	file.write((const char*)&sizeOfName, sizeof(int));
	file.write((const char*)name, sizeof(char) * sizeOfName);

	file.write((const char*)&sizeOfContractor, sizeof(int));
	file.write((const char*)contractor, sizeof(char) * sizeOfContractor);

	file.write((const char*)&duration, sizeof(double));

}

void Song::readFromBinary(std::ifstream& file) 
{

	int sizeOfName = 0;
	int sizeOfContractor = 0;

	delete[] this->name;
	delete[] this->contractor;

	file.read((char*)&sizeOfName, sizeof(int));
	this->name = new char[sizeOfName];
	file.read((char*)this->name, sizeof(char) * sizeOfName);

	file.read((char*)&sizeOfContractor, sizeof(int));
	this->contractor = new char[sizeOfContractor];
	file.read((char*)this->contractor, sizeof(char) * sizeOfContractor);

	file.read((char*)&duration, sizeof(double));

}
