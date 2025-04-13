#include "SetByString.h"

int main() 
{

	SetByString s1(10, "1 2 3");
	s1.print();
	s1.setAt(1, '0');
	s1.print();
	s1.setAt(1, ' ');
	s1.print();

	return 0;

}

