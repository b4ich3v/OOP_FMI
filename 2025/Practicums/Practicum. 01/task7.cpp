#include <iostream>

enum class Options
{
	
	A = 0,
	B = 1,
	C = 2,
	D = 3

};

struct Question
{
public:

	char tittle[51];
	char answers[4][51];
	Options validOption;
	int points;

};

struct Test 
{
public:

	Question questions[6];

};

int main()
{

	Question q0 = { "What is 1 + 1", "1", "2", "3", "4", Options::A, 10};
	Question q1 = { "What is 2 * 1", "1", "2", "3", "4", Options::B, 10 };
	Question q2 = { "What is 1 - 1", "1", "2", "3", "4", Options::C, 10 };
	Question q3 = { "What is 1 / 1", "1", "2", "3", "4", Options::D, 10 };
	Question q4 = { "What is 100 | 0", "1", "2", "3", "4", Options::A, 10 };
	Question q5 = { "What is 1 ^ 1", "1", "2", "3", "4", Options::B, 10 };

	Test test;
	test.questions[0] = q0;
	test.questions[1] = q1;
	test.questions[2] = q2;
	test.questions[3] = q3;
	test.questions[4] = q4;
	test.questions[5] = q5;

	int countOfPoints = 0;

	for (int i = 0; i < 6; i++)
	{
		
		int option = 0;

		std::cout << test.questions[i].tittle << std::endl;
		std::cout << "The points you can get from this question are: " << test.questions[i].points << std::endl;

		std::cout << "A :" << test.questions[i].answers[0] << std::endl;
		std::cout << "B :" << test.questions[i].answers[1] << std::endl;
		std::cout << "C :" << test.questions[i].answers[2] << std::endl;
		std::cout << "D :" << test.questions[i].answers[3] << std::endl;

		std::cin >> option;

		if (option == (int)test.questions[i].validOption) 
		{

			countOfPoints += test.questions[i].points;

		}

	}

	std::cout << countOfPoints;
	return 0;

}
