#include "MulString.h"

int main()
{

	MyString str1("Yoan");
	MyString str2(" Baychev");

	str1 += str2;

	MulString s1(str1);
	MulString s2("ABCDEFrrrru1111ahjdaaaaaaahu192");
	std::cout << s1;

	MulString result1 = s1 % s2;
	std::cout << result1;
	std::cout << s1 % MulString(" ");

	MulString s3('4');
	MulString result2 = s3 * 3;
	std::cout << result2;

	MulString s4("Shte slusham ");
	std::cout << s4 * 3;

	return 0;

}
