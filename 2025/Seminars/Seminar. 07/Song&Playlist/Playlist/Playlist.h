#include "Song.h"
#pragma once

class Playlist
{
private:

	Song* songs = nullptr;
	int countOfSongs = 0;
	int capacity = 8;

	void free();

	void copyFrom(const Playlist& other);

	void resize(int newCapacity);

public:

	Playlist();

	Playlist(const Playlist& other);

	Playlist& operator = (const Playlist& other);

	~Playlist();

	void addSong(const Song& song);

	void removeSong(const Song& song);

	void removeSong(int index);

	friend std::ostream& operator << (std::ostream& os, const Playlist& p);

	friend std::istream& operator >> (std::istream& is, Playlist& p);

	void writeToBinaryFile(const char* fileName) const;

	void readFromBinaryFile(const char* fileName);

};
