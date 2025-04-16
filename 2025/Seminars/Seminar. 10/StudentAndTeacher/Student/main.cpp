#include "Student.h"
#include <iostream>

int main()
{

	Student s1("Yoan Baychev", 20, "0MI060328");
	Student s2("Ilian Zaprqnov", 21, "2MI360323");
	Student s3("Kaloqn Markov", 21, "0MI061221");
	Student s4("Ivailo Kunchev", 20, "4MI0600321");

	std::cout << s1.getStudentName() << " " << s1.getStudentAge() << " " << s1.getStudentId() <<std::endl;
	std::cout << s2.getStudentName() << " " << s2.getStudentAge() << " " << s2.getStudentId() <<std::endl;
	std::cout << s3.getStudentName() << " " << s3.getStudentAge() << " " << s3.getStudentId() <<std::endl;
	std::cout << s4.getStudentName() << " " << s4.getStudentAge() << " " << s4.getStudentId() <<std::endl;

	return 0;

}

