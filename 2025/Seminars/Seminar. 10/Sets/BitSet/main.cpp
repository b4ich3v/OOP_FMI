#include "BitSet.h"

int main()
{

	BitSet s1(100);
	s1.addNumber(1);
	s1.addNumber(13);
	s1.addNumber(67);
	s1.addNumber(3);
	s1.addNumber(11);

	BitSet s2(3);
	s2.addNumber(1);
	s2.addNumber(13);
	s2.addNumber(67);
	s2.addNumber(56);
	s2.addNumber(111);
	s2.addNumber(0);

	BitSet unionOfTwo = s1 | s2;
	BitSet intersectionOfTwo = s1 & s2;

	unionOfTwo.printSet();
	std::cout << std::endl;
	intersectionOfTwo.printSet();

	return 0;

}
