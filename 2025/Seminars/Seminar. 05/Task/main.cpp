#include "Task.h"

int main()
{

	Time time1(10, 0, 0);
	Time time2(14, 27, 31);
	Time time3(9, 56, 8);
	Time time4(18, 20, 22);

	Task t1("Clean_my_room", 10, 60, time1);
	Task t2("Do_my_homework", 256, 100, time2);
	Task t3("Play_games", 0, 120, time3);
	Task t4("Study_for_OOP_exam", 256, 600, time4);

	t1.printTask();
	t2.printTask();
	t3.printTask();
	t4.printTask();

	std::cout << std::endl;

	if (t4 > t2) std::cout << "OOP on top" << std::endl;
	if (t1 < t2) std::cout << "Dirty room" << std::endl;

	std::cout << std::endl;

	std::ofstream file1("result.txt");
	t4.writeToTxt(file1);
	file1.close();

	std::ifstream file2("result.txt");
	Task readTask(file2);
	file2.close();
	readTask.printTask();

	readTask.setStatusTrue();
	readTask.printTask();

	return 0;

}
