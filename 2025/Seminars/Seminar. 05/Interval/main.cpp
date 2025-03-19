#include "Interval.h"

int main()
{

	Interval interval1(-1, 15);
	Interval interval2(-5, 9);

	interval1.intersection(interval2);
	interval1.print();

	Interval interval3(1, 64);
	std::cout << interval3.areStartAndEndAPOT() << std::endl;
	std::cout << interval3.countOfNumbersWDDInInterval() << std::endl;
	std::cout << interval3.countOfPalindromesInInterval() << std::endl;
	std::cout << interval3.countOfPrimesInInterval() << std::endl;

	std::cout << interval3.isSubinterval(Interval(5, 16)) << std::endl;
	std::cout << interval3.isInInterval(27) << std::endl;

	return 0;

}
