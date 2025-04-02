#include "Song.h"
#include <fstream>

int main()
{

	Song s1("Mazna", "Vankata", 3.18);
	Song s2("No mercy", "Cj", 4.51);
	Song s3("Skibidi", "Son", 2.68);
	Song s4("Bombandiro Krokodilo", "VanG", 3.56);

	Song newSong = s1;
	newSong = s4;
	std::cout << newSong;

	std::ofstream file("test.txt");
	file << s1 << s2 << s3;

	return 0;

}
