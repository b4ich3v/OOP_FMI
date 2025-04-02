#include "Song.h"
#include "Playlist.h"
#include <fstream>

int main()
{

	Song s1("Mazna", "Vankata", 3.18);
	Song s2("No mercy", "Cj", 4.51);
	Song s3("Skibidi", "Son", 2.68);
	Song s4("Bombandiro Krokodilo", "VanG", 3.56);

	Playlist p1;
	p1.addSong(s1);
	p1.addSong(s2);
	p1.addSong(s3);
	p1.addSong(s4);
	std::cout << p1;
	p1.writeToBinaryFile("file.dat");

	std::cout << std::endl;

	Playlist p2;
	p2.readFromBinaryFile("file.dat");
	std::cout << p2;

	std::cout << std::endl;

	p2.removeSong(3);
	p2.removeSong(2);
	std::cout << p2;

	return 0;

}
