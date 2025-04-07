#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS
{

	const int COUNT_OF_BITS_IN_BYTE = 8;

	void upperCurrentBit(char& byte, int index)
	{

		byte |= (1 << index);

	}

	bool isUpperInt(uint8_t byte, int index)
	{

		return (byte & (1 << index));

	}

}

enum class Genre : uint8_t
{

	ROCK = (1 << 0),
	POP = (1 << 1),
	HIP_POP = (1 << 2),
	ELECTRONIC_MUSIC = (1 << 3),
	JAZZ = (1 << 4),

};

class Content
{
private:

	char* data = nullptr;

	void free()
	{

		delete[] data;
		data = nullptr;

	}

	void copyFrom(const Content& other)
	{

		data = new char[strlen(other.data) + 1] {0};
		strncpy(data, other.data, strlen(other.data));
		this->data[strlen(other.data)] = '\0';

	}

public:

	Content() = default;

	Content(const char* data)
	{

		this->data = new char[strlen(data) + 1];
		strncpy(this->data, data, strlen(data));
		this->data[strlen(data)] = '\0';

	}

	Content(std::ifstream& file)
	{

		if (!file.is_open()) throw std::logic_error("Error");

		free();

		int sizeOfData = 0;

		file.read((char*)&sizeOfData, sizeof(int));
		data = new char[sizeOfData + 1] {0};
		file.read((char*)data, sizeOfData);
		this->data[sizeOfData] = '\0';

	}

	Content(const Content& other)
	{

		copyFrom(other);

	}

	Content& operator  = (const Content& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	char& operator [] (int index)
	{

		return data[index];

	}

	const char& operator [] (int index) const
	{

		return data[index];

	}

	~Content()
	{

		free();

	}

	void addRythm(int k)
	{

		if (k < 0) return;

		int size = strlen(data);
		int countOfBits = HELPERS::COUNT_OF_BITS_IN_BYTE * size;

		for (int i = 0; i < countOfBits; i++)
		{

			if ((i + 1) % k == 0)
			{

				int byteIndex = i / HELPERS::COUNT_OF_BITS_IN_BYTE;
				int bitIndex = i % HELPERS::COUNT_OF_BITS_IN_BYTE;
				HELPERS::upperCurrentBit(data[byteIndex], bitIndex);

			}

		}

	}

	int getSize() const
	{

		return strlen(data);

	}

	void printContent() const
	{

		std::cout << data << std::endl;

	}

	char getCurrentByteCopy(int index) const
	{

		return data[index];

	}

	char& getCurrentByteRef(int index)
	{

		return data[index];

	}

};

class Song
{
private:

	char* name = nullptr;
	double duration = 0;
	uint8_t genre = 0;
	Content content;

	void free()
	{

		delete[] name;
		name = nullptr;
		duration = 0;

	}

	void copyFrom(const Song& other)
	{

		this->name = new char[strlen(other.name) + 1];
		strncpy(this->name, other.name, strlen(other.name));
		this->name[strlen(other.name)] = '\0';
		this->content = other.content;
		this->duration = other.duration;
		this->genre = other.genre;

	}

public:

	Song() = default;

	Song(const char* name, double duration, const Content& content, uint8_t genre = 0)
	{

		this->name = new char[strlen(name) + 1];
		strncpy(this->name, name, strlen(name));
		this->name[strlen(name)] = '\0';
		this->content = content;
		this->duration = duration;
		this->genre = genre;

	}

	Song(const Song& other)
	{

		copyFrom(other);

	}

	Song& operator = (const Song& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Song()
	{

		free();

	}

	void mixWithOtherSong(const Song& other)
	{

		int iter = std::min(content.getSize(), other.content.getSize());

		for (int i = 0; i < iter; i++)
		{

			content[i] ^= other.content[i];
		}

	}

	void combineWithOtherGenre(Genre genre)
	{

		this->genre |= (uint8_t)genre;

	}

	void combineWithOtherGenre(uint8_t genres)
	{

		this->genre |= genres;

	}

	void printSong() const
	{

		std::cout << name << std::endl;
		std::cout << duration << std::endl;

		bool hasGenre = false;

		for (int i = 0; i < HELPERS::COUNT_OF_BITS_IN_BYTE; i++)
		{

			if (HELPERS::isUpperInt(genre, i))
			{

				switch ((Genre)(1 << i))
				{

				case Genre::ROCK: std::cout << "ROCK "; break;
				case Genre::POP: std::cout << "POP "; break;
				case Genre::HIP_POP: std::cout << "HIP_POP "; break;
				case Genre::ELECTRONIC_MUSIC: std::cout << "ELECTRONIC_MUSIC "; break;
				case Genre::JAZZ: std::cout << "JAZZ "; break;
				default: break;

				}

				hasGenre = true;

			}

		}

		if (!hasGenre) std::cout << "No current genre";

		std::cout << std::endl;
		content.printContent();

	}

};

int main()
{

	const int size1 = 69;
	const int size2 = 30;

	char ptr1[size1] = "Kolko mnogo mrazq fmi i kursa po obektno-orientirano programirane!!!";
	char ptr2[size2] = "Kolko mnogo obicham DSTR{1,2}";

	std::ofstream file1("file.dat", std::ios::binary);
	file1.write((const char*)&size1, sizeof(int));
	file1.write((const char*)ptr1, size1 * sizeof(uint8_t));
	file1.close();

	std::ifstream file2("file.dat", std::ios::binary);
	Content content1(file2);
	file2.close();

	Content content2(ptr2);
	content2.addRythm(2);
	content2.addRythm(3);

	Song song1("Pesen za fmi", 4.56, content1);
	song1.combineWithOtherGenre(Genre::ROCK);
	song1.combineWithOtherGenre((uint8_t)Genre::ELECTRONIC_MUSIC | (uint8_t)Genre::HIP_POP);
	song1.printSong();

	std::cout << std::endl;

	Song song2("Pesen za fmi 2ra chast", 3.78, content2);
	song2.printSong();

	std::cout << std::endl;

	song1.mixWithOtherSong(song2);
	song1.printSong();

	return 0;

}
