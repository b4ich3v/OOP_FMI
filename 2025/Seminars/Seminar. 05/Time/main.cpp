#include "Time.h"

int main()
{

	Time time1(21, 20, 58);
	Time time2(5, 9, 19);

	time1.printTime();
	time2.printTime();

	Time leftToMidnight = time1.timeLeftToMidnight();
	leftToMidnight.printTime();

	Time diffTime = time1.differenceOfTwo(time2);
	diffTime.printTime();

	std::cout << time1.isDinnerTime() << std::endl;
	std::cout << time2.isPartyTime() << std::endl;

	time1.tick();
	time1.tick();
	time1.printTime();

	return 0;

}
