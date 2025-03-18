#include <iostream>
#include <cstring>

class Song
{
private:

    char* name = nullptr;
    double duration = 0;

    void copyFrom(const Song& other) 
    {

        char* newName = new char[strlen(other.name) + 1];
        strncpy(newName, other.name, strlen(other.name));
        newName[strlen(other.name)] = '\0';

        delete[] this->name;
        this->name = newName;
        this->duration = other.duration;

    }

    void free() 
    {

        delete[] name;
        name = nullptr;
        duration = 0;

    }

public:

    Song(): name(nullptr), duration(0) {}

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

    Song(const char* name, double duration)
    {

        if (this->name != nullptr)
        {

            delete[] this->name;

        }
        
        this->name = new char[strlen(name) + 1];
        strncpy(this->name, name, strlen(name));
        this->name[strlen(name)] = '\0';

        this->duration = duration;

    }

    ~Song()
    {

        free();

    }

    bool operator == (const Song& other) const
    {

        return !(strcmp(this->name, other.name)) && (this->duration == other.duration);

    }

    bool operator != (const Song& other) const
    {

        return !(*this == other);

    }

    void printSong() const 
    {

        std::cout << name << " ";
        std::cout << duration << std::endl;

    }

};

class Playlist
{
private:

    Song* songs = nullptr;
    int countOfSongs = 0;
    int capacity = 8;

    void resize(int newCapacity) 
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

    void copyFrom(const Playlist& other) 
    {

        Song* newSongs = new Song[other.capacity];

        for (int i = 0; i < other.countOfSongs; i++)
        {

            newSongs[i] = other.songs[i];

        }

        delete[] songs;
        songs = newSongs;
        countOfSongs = other.countOfSongs;
        capacity = other.capacity;

    }

    void free()
    {

        delete[] songs;
        songs = nullptr;
        countOfSongs = 0;

    }

public:

    Playlist()
    {

        countOfSongs = 0;
        capacity = 8;
        songs = new Song[capacity];

    }

    Playlist(const Song* songs, int countOfSongs) 
    {

        if (countOfSongs > 0 && songs != nullptr) 
        {

            this->countOfSongs = countOfSongs;

            if (countOfSongs >= capacity) resize(capacity * 2);

            this->songs = new Song[capacity];

            for (int i = 0; i < countOfSongs; i++)
            {

                this->songs[i] = songs[i];

            }

        }        

    }

    Playlist(const Playlist& other) 
    {

        copyFrom(other);

    }

    Playlist& operator = (const Playlist& other) 
    {

        if (this != &other)
        {

            free();
            copyFrom(other);

        }

        return *this;

    }

    ~Playlist()
    {

        free();

    }

    void addSong(const Song& song)
    {

        if (countOfSongs == capacity) resize(capacity * 2);

        songs[countOfSongs] = song;
        countOfSongs += 1;

    }

    void removeSong(const Song& song)
    {

        for (int i = 0; i < countOfSongs; i++)
        {

            if (songs[i] == song)
            {

                std::swap(songs[countOfSongs - 1], songs[i]);
                countOfSongs--;
                break;

            }

        }

    }

    void printPlaylist() const 
    {

        for (int i = 0; i < countOfSongs; i++)
        {

            songs[i].printSong();

        }

        std::cout << std::endl;

    }

};

int main()
{

    Song song1("How bad do you want it", 3.14);
    Song song2("Follow the leader", 2.76);
    Song song3("Game over", 4.20);
    Song song4("Bumpy ride", 4.22);
    Song song5("Candy", 2.38);

    Song song6("Baby", 2.58);
    Song song7("Balkan", 3.27);

    Song* songs = new Song[5];
    songs[0] = song1;
    songs[1] = song2;
    songs[2] = song3;
    songs[3] = song4;
    songs[4] = song5;

    Playlist playlist(songs, 5);
    playlist.printPlaylist();

    playlist.addSong(song6);
    playlist.addSong(song7);
    playlist.printPlaylist();

    playlist.removeSong(song3);
    playlist.printPlaylist();

    delete[] songs;
    return 0;

}
