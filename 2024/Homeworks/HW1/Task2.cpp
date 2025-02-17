#include <iostream>
#include <fstream>
#include <cstring>

#pragma warning(disable:4996)

namespace GlobalConstants
{

    const int MAX_NAME_LENGTH = 64;
    const int MAX_CONTENT_SIZE = 256;
    const int MAX_COUNT_OF_SONGS = 30;

}

enum Genre : uint8_t
{

    NONE = 0,
    ROCK = 1 << 0,
    POP = 1 << 1,
    HIP_HOP = 1 << 2,
    ELECTRONIC = 1 << 3,
    JAZZ = 1 << 4

};

char* genreToString(Genre genre)
{

    char* genresStr = new char[128];
    genresStr[0] = '\0';

    if (genre == NONE)
    {

        strcpy(genresStr, "None");

    }
    else
    {

        bool added = false;

        // Check each genre bit in the genre variable. If a bit is set, concatenate
        // the corresponding genre name to genresStr. If a genre name is already added,
        // prepend " & " to subsequent genre names for readability.
        if (genre & ROCK) { strcat(genresStr, added ? " & Rock" : "Rock"); added = true; }
        if (genre & POP) { strcat(genresStr, added ? " & Pop" : "Pop"); added = true; }
        if (genre & HIP_HOP) { strcat(genresStr, added ? " & Hip-Hop" : "Hip-Hop"); added = true; }
        if (genre & ELECTRONIC) { strcat(genresStr, added ? " & Electronic" : "Electronic"); added = true; }
        if (genre & JAZZ) { strcat(genresStr, added ? " & Jazz" : "Jazz"); }

    }

    return genresStr;

}

struct Song
{

    char name[GlobalConstants::MAX_NAME_LENGTH + 1];
    int duration;
    Genre genre;
    uint8_t content[GlobalConstants::MAX_CONTENT_SIZE];
    int contentSize;

    Song() : duration(0), genre(NONE), contentSize(0)
    {

        name[0] = '\0';

    }

    Song(const char* inputName, int inputHours, int inputMinutes, int inputSeconds, Genre inputGenre, const char* fileName)
    {

        strncpy(this->name, inputName, GlobalConstants::MAX_NAME_LENGTH);
        this->name[GlobalConstants::MAX_NAME_LENGTH] = '\0';
        this->duration = inputHours * 3600 + inputMinutes * 60 + inputSeconds;
        this->genre = inputGenre;
        this->contentSize = readContentFromFile(fileName);

    }

    bool readContentFromFile(const char* fileName)
    {

        std::ifstream file(fileName, std::ios::binary);

        if (!file.is_open())
        {

            std::cout << "Cannot open file" << std::endl;
            return false;

        }

        char buffer;
        contentSize = 0;

        while (file.read(&buffer, 1) && contentSize < GlobalConstants::MAX_CONTENT_SIZE)
        {

            content[contentSize++] = buffer;

        }

        if (file.fail() && !file.eof())
        {

            std::cout << "Error reading file" << std::endl;
            file.close();
            return false;

        }

        file.close();
        return true;

    }

    void addRhythm(int k)
    {

        for (int i = 0; i < contentSize; i++) // Iterate over each byte of the song's content
        {

            // Within each byte, set bits to 1 at intervals of 'k'
            // The loop starts from the most significant bit (bit 7) and moves towards the least significant bit (bit 0), decreasing by 'k' each step
            // This ensures that the pattern is applied evenly across the byte
            for (int bit = 7; bit >= 0; bit = bit - k)
            {

                // Use bitwise OR to set the specified bit to 1 without altering the other bits of the byte
                // '1 << bit' creates a mask with a 1 at the 'bit' position and 0s elsewhere, 
                // which is then ORed with the current byte, effectively setting the 'bit' position to 1
                content[i] |= 1 << bit;

            }

        }

    }

    Genre parseGenreStr(const char* inputGenreInString)
    {

        Genre genre = NONE;

        while (*inputGenreInString != '\0') // Iterate through each character of the input string until the null terminator is reached
        {

            switch (*inputGenreInString) // Check the current character and update the genre variable accordingly
            {

            case 'r': {genre = (Genre)(genre | ROCK); break;}
            case 'p': {genre = (Genre)(genre | POP); break;}
            case 'h': {genre = (Genre)(genre | HIP_HOP); break;}
            case 'e': {genre = (Genre)(genre | ELECTRONIC); break;}
            case 'j': {genre = (Genre)(genre | JAZZ); break;}
            default: {std::cout << "Unknown genre symbol" << std::endl;  break;}

            }

            inputGenreInString++; // Move to the next character in the input string

        }

        return genre;

    }

    void mixWith(const Song& inputSong)
    {

        int mixLength = contentSize; // Determine the length of the shorter song to avoid accessing out of bounds

        if (inputSong.contentSize < contentSize)
        {

            mixLength = inputSong.contentSize;

        }

        for (int i = 0; i < mixLength; i++) // Iterate over each byte up to the length of the shorter song
        {

            // Apply a bitwise XOR followed by a bitwise AND NOT to each byte
            // The XOR operation mixes the bits of the two songs' content,
            // and the AND NOT operation ensures that bits set in both songs are turned off in the result
            // This could create a unique effect where similar bits cancel out, emphasizing the differences
            content[i] = (content[i] ^ inputSong.content[i]) & ~(content[i] & inputSong.content[i]);

        }

    }

};

class Playlist
{
private:

    Song songs[GlobalConstants::MAX_COUNT_OF_SONGS];
    int songCount = 0;

public:

    int getSongCount() const
    {

        return songCount;

    }

    const Song& getSong(int inputIndex) const
    {

        if (inputIndex < 0 || inputIndex >= songCount)
        {

            return {};

        }

        return songs[inputIndex];

    }

    void add(const char* inputName, int inputHours, int inputMinutes, int inputSeconds, const char* inputGenreInString, const char* fileName)
    {

        if (songCount >= GlobalConstants::MAX_COUNT_OF_SONGS)
        {

            std::cout << "Playlist is full" << std::endl;
            return;

        }

        Song tempSong;
        Genre genre = tempSong.parseGenreStr(inputGenreInString); // Convert inputGenreInString to Genre enum

        songs[songCount] = Song(inputName, inputHours, inputMinutes, inputSeconds, genre, fileName); // Add the new song to the playlist at the current index (songCount), then increment the song count
        songCount++;

    }

    void printSongs() const
    {

        for (int i = 0; i < songCount; i++)
        {

            std::cout << "Name: " << songs[i].name
                << ", Duration: " << songs[i].duration / 3600 << " hours "
                << (songs[i].duration % 3600) / 60 << " minutes "
                << songs[i].duration % 60 << " seconds, Genre: "
                << genreToString(songs[i].genre) << std::endl;

        }

    }

    int findSongByName(const char* inputName) const
    {

        for (int i = 0; i < songCount; i++)
        {

            if (strcmp(songs[i].name, inputName) == 0)
            {

                return i;

            }

        }

        return -1;

    }

    void findSongsByGenre(Genre inputGenre) const
    {

        bool isFound = false;

        for (int i = 0; i < songCount; i++)
        {

            if (songs[i].genre & inputGenre) // Checks if the genre of the current song matches the search
            {

                std::cout << "Found" << std::endl;
                isFound = true;

            }

        }

        if (!isFound)
        {

            std::cout << "No songs found for this genre" << std::endl;

        }

    }

    void sortByDuration()
    {

        bool swapped;

        do
        {

            swapped = false;

            for (int i = 0; i < songCount - 1; i++)
            {

                if (songs[i].duration > songs[i + 1].duration)
                {

                    std::swap(songs[i], songs[i + 1]);
                    swapped = true;

                }

            }

        }

        while (swapped);

    }

    void sortByName()
    {

        bool swapped;

        do
        {

            swapped = false;

            for (int i = 0; i < songCount - 1; i++)
            {

                if (std::strcmp(songs[i].name, songs[i + 1].name) > 0)
                {

                    std::swap(songs[i], songs[i + 1]);
                    swapped = true;

                }

            }

        }

        while (swapped);

    }

    void modifySongByName(const char* inputName, int inputMethod, int k = 0, const Song* inputSong = nullptr)
    {

        int index = findSongByName(inputName); // Find the index of the song with the given name in the playlist

        if (index != -1)
        {

            switch (inputMethod) // Determine the modification method based on inputMethod
            {

            case 1: { songs[index].addRhythm(k); break;}
            case 2: {
                if (inputSong != nullptr)
                {

                    songs[index].mixWith(*inputSong);

                } break;}
            default: { std::cout << "Unknown modification method" << std::endl;  break;}

            }

        }
        else
        {

            std::cout << "Song not found" << std::endl;

        }

    }

    void saveSongToFile(const char* songName, const char* fileName)
    {

        int index = findSongByName(songName);

        if (index != -1)
        {

            std::ofstream file(fileName, std::ios::binary);

            if (file.is_open())
            {

                file.write((const char*)(songs[index].content), songs[index].contentSize);
                file.close();
                std::cout << "Song saved to file" << std::endl;

            }
            else
            {

                std::cout << "Failed to open file for writing" << std::endl;

            }

        }
        else
        {

            std::cout << "Song not found: " << songName << std::endl;

        }

    }

};

void freDynamicallyAssignedGenres(Playlist& inputPlaylist)
{

    for (int i = 0; i < inputPlaylist.getSongCount(); i++) // Iterate over each song in the playlist
    {

        char* genreStr = genreToString(inputPlaylist.getSong(i).genre); // Dynamically allocate a string for the genre of the current song using genreToString

        delete[] genreStr; // Immediately free the allocated memory to prevent memory leaks

    }

}

int main1()
{

    Playlist myPlaylist;

    myPlaylist.add("Song 1", 0, 3, 15, "rpjjrppj", "song1.dat");
    myPlaylist.add("Song 2", 0, 4, 20, "p", "song2.dat");

    std::cout << "Initial Playlist:" << std::endl;
    myPlaylist.printSongs();

    freDynamicallyAssignedGenres(myPlaylist);

    return 0;

}

