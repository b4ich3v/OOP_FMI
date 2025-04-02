#include "Playlist.h"

void Playlist::free() 
{

	delete[] songs;
	songs = nullptr;

	capacity = 8;
	countOfSongs = 0;

}

void Playlist::copyFrom(const Playlist& other) 
{

	songs = new Song[other.capacity];

	for (int i = 0; i < other.countOfSongs; i++)
	{

		songs[i] = other.songs[i];

	}

	countOfSongs = other.countOfSongs;
	capacity = other.capacity;

}

void Playlist::resize(int newCapacity) 
{

	if (newCapacity <= capacity) return;

	Song* newSongs = new Song[newCapacity];

	for (int i = 0; i < countOfSongs; i++)
	{

		newSongs[i] = songs[i];

	}

	delete[] songs;
	songs = newSongs;
	capacity = newCapacity;

}

Playlist::Playlist() 
{

	countOfSongs = 0;
	capacity = 8;
	songs = new Song[capacity];

}

Playlist::Playlist(const Playlist& other) 
{

	copyFrom(other);

}

Playlist& Playlist::operator = (const Playlist& other) 
{

	if (this != &other)
	{

		free();
		copyFrom(other);

	}

	return *this;

}

Playlist::~Playlist() 
{

	free();

}

void Playlist::addSong(const Song& song) 
{

	if (countOfSongs == capacity) resize(capacity * 2);

	songs[countOfSongs] = song;
	countOfSongs += 1;

}

void Playlist::removeSong(const Song& song) 
{

	for (int i = 0; i < countOfSongs; i++)
	{

		if(!strcmp(song.getName(), songs[i].getName()) &&
		   !strcmp(song.getContractor(), songs[i].getContractor()) &&
		   song.getDuration() == songs[i].getDuration()) 
		{

			std::swap(songs[i], songs[countOfSongs - 1]);
			countOfSongs -= 1;
			break;

		}

	}

}

void Playlist::removeSong(int index) 
{

	removeSong(songs[index]);

}

std::ostream& operator << (std::ostream& os, const Playlist& p)
{

	os << p.capacity << " ";
	os << p.countOfSongs << std::endl;

	for (int i = 0; i < p.countOfSongs ; i++)
	{

		os << p.songs[i];

	}

	return os;

}

std::istream& operator >> (std::istream& is, Playlist& p) 
{

	int countOfSongs = 0;
	int capacity = 0;

	is >> countOfSongs >> capacity;
	is.ignore(1);

	delete[] p.songs;
	p.songs = new Song[capacity];
	p.capacity = capacity;
	p.countOfSongs = countOfSongs;

	for (int i = 0; i < p.countOfSongs; i++)
	{

		is >> p.songs[i];

	}

	return is;

}

void Playlist::writeToBinaryFile(const char* fileName) const 
{

	std::ofstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file << capacity << " ";
	file << countOfSongs << std::endl;

	for (int i = 0; i < countOfSongs; i++)
	{

		songs[i].writeToBinary(file);

	}

	file.close();

}

void Playlist::readFromBinaryFile(const char* fileName) 
{

	std::ifstream file(fileName, std::ios::binary);

	if (!file.is_open()) return;

	file >> capacity;
	file >> countOfSongs;
	file.ignore(1);

	for (int i = 0; i < countOfSongs; i++)
	{

		songs[i].readFromBinary(file);

	}

	file.close();

}
