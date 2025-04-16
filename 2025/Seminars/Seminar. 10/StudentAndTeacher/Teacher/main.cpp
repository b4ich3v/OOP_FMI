#include "Teacher.h"
#include <iostream>

int main()
{

	char** subjects1 = new char* [3];
	for (int i = 0; i < 3; i++) subjects1[i] = new char[10];
	strncpy(subjects1[0], "Geometry", strlen("Geometry"));
	subjects1[0][strlen("Geometry")] = '\0';
	strncpy(subjects1[1], "DSA", strlen("DSA"));
	subjects1[1][strlen("DSA")] = '\0';
	strncpy(subjects1[2], "OOP", strlen("OOP"));
	subjects1[2][strlen("OOP")] = '\0';

	char** subjects2 = new char* [2];
	for (int i = 0; i < 2; i++) subjects2[i] = new char[10];
	strncpy(subjects2[0], "DIS2", strlen("DIS2"));
	subjects2[0][strlen("DIS2")] = '\0';
	strncpy(subjects2[1], "USI", strlen("USI"));
	subjects2[1][strlen("USI")] = '\0';

	char** subjects3 = new char* [4];
	for (int i = 0; i < 4; i++) subjects3[i] = new char[10];
	strncpy(subjects3[0], "Geometry", strlen("Geometry"));
	subjects3[0][strlen("Geometry")] = '\0';
	strncpy(subjects3[1], "UP", strlen("UP"));
	subjects3[1][strlen("UP")] = '\0';
	strncpy(subjects3[2], "DSTR1", strlen("DSTR1"));
	subjects3[2][strlen("DSTR1")] = '\0';
	strncpy(subjects3[3], "DSTR2", strlen("DSTR2"));
	subjects3[3][strlen("DSTR2")] = '\0';

	char** subjects4 = new char* [1];
	for (int i = 0; i < 1; i++) subjects4[i] = new char[10];
	strncpy(subjects4[0], "OOP", strlen("OOP"));
	subjects4[0][strlen("OOP")] = '\0';

	Teacher t1("Yoan Baychev", 20, subjects1, 3);
	Teacher t2("Ilian Zaprqnov", 21, subjects2, 2);
	Teacher t3("Kaloqn Markov", 21, subjects3, 4);
	Teacher t4("Ivailo Kunchev", 20, subjects4, 1);

	std::cout << t1.getTeacherName() << " " << t1.getTeacherAge() << std::endl;
	int iter1 = t1.getCountOfSubjects();
	const char* const* sub1 = t1.getTeacherSubjects();
	for (int i = 0; i < iter1; i++) std::cout << sub1[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << t2.getTeacherName() << " " << t2.getTeacherAge() << std::endl;
	int iter2 = t2.getCountOfSubjects();
	const char* const* sub2 = t2.getTeacherSubjects();
	for (int i = 0; i < iter2; i++) std::cout << sub2[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << t3.getTeacherName() << " " << t3.getTeacherAge() << std::endl;
	int iter3 = t3.getCountOfSubjects();
	const char* const* sub3 = t3.getTeacherSubjects();
	for (int i = 0; i < iter3; i++) std::cout << sub3[i] << " ";
	std::cout << std::endl << std::endl;

	std::cout << t4.getTeacherName() << " " << t4.getTeacherAge() << std::endl;
	int iter4 = t4.getCountOfSubjects();
	const char* const* sub4 = t4.getTeacherSubjects();
	for (int i = 0; i < iter4; i++) std::cout << sub4[i] << " ";
	std::cout << std::endl << std::endl;

	for (int i = 0; i < 3; i++) delete[] subjects1[i];
	for (int i = 0; i < 2; i++) delete[] subjects2[i];
	for (int i = 0; i < 4; i++) delete[] subjects3[i];
	for (int i = 0; i < 1; i++) delete[] subjects4[i];

	delete[] subjects1;
	delete[] subjects2;
	delete[] subjects3;
	delete[] subjects4;

	return 0;

}
