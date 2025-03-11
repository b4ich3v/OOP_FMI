#include <iostream>
#include <fstream>
#include <cstring>

namespace CONSTANTS
{

	const int MAX_SIZE_TASKS = 20;

}

class Task
{
private:

	char* name = nullptr;
	char* description = nullptr;;
	int points = 0;

	void free()
	{

		delete[] name;
		delete[] description;
		name = nullptr;
		description = nullptr;
		points = 0;

	}

	void copyFrom(const Task& other)
	{

		changeName(other.name);
		changeDescription(other.description);
		changePoints(other.points);

	}

public:

	Task() = default;

	Task(const char* newName, const char* newDescription, int newPoints)
	{

		changeName(newName);
		changeDescription(newDescription);
		changePoints(newPoints);

	}

	Task(const Task& other)
	{

		copyFrom(other);

	}

	Task& operator = (const Task& other)
	{

		if (this != &other)
		{

			free();
			copyFrom(other);

		}

		return *this;

	}

	~Task()
	{

		free();

	}

	void changeName(const char* newName)
	{

		if (!newName) return;

		if (name != nullptr)
		{

			char* finalName = new char[strlen(newName) + 1];
			strncpy(finalName, newName, strlen(newName));
			finalName[strlen(newName)] = '\0';

			delete[] name;
			name = finalName;

		}
		else
		{

			name = new char[strlen(newName) + 1];
			strncpy(name, newName, strlen(newName));
			name[strlen(newName)] = '\0';

		}

	}

	void changeDescription(const char* newDescription)
	{

		if (!newDescription) return;

		if (name != nullptr)
		{

			char* finalDescription = new char[strlen(newDescription) + 1];
			strncpy(finalDescription, newDescription, strlen(newDescription));
			finalDescription[strlen(newDescription)] = '\0';

			delete[] description;
			description = finalDescription;

		}
		else
		{

			description = new char[strlen(newDescription) + 1];
			strncpy(description, newDescription, strlen(newDescription));
			description[strlen(newDescription)] = '\0';

		}

	}

	void changePoints(int newPoints)
	{

		if (newPoints < 0) return;

		points = newPoints;

	}

	void printTask() const
	{

		std::cout << name << " ";
		std::cout << description << " ";
		std::cout << points << std::endl;

	}

	void writeToFile(std::ofstream& file)
	{

		if (!file.is_open()) return;

		int nameLen = strlen(name);
		file.write((const char*)&nameLen, sizeof(int));
		file.write((const char*)name, nameLen * sizeof(char));

		int descriptionLen = strlen(description);
		file.write((const char*)&descriptionLen, sizeof(int));
		file.write((const char*)description, descriptionLen * sizeof(char));

		file.write((const char*)&points, sizeof(int));

	}

	Task readFromFile(std::ifstream& file)
	{

		if (!file.is_open()) return {};

		Task result;

		int nameLen = 0;
		file.read((char*)&nameLen, sizeof(int));
		if (result.name != nullptr) delete[] result.name;
		result.name = nullptr;
		result.name = new char[nameLen + 1];
		file.read((char*)result.name, nameLen * sizeof(char));

		int descriptionLen = 0;
		file.read((char*)&descriptionLen, sizeof(int));
		if (result.description != nullptr) delete[] result.description;
		result.description = nullptr;
		result.description = new char[descriptionLen + 1];
		file.read((char*)result.description, descriptionLen * sizeof(char));

		file.read((char*)&result.points, sizeof(int));

		return result;

	}

};

class Exam
{
private:

	Task tasks[CONSTANTS::MAX_SIZE_TASKS];
	int countOfTasks = 0;
	int minPointToPass = 10;

public:

	Exam() = default;

	void addTask(const Task& task)
	{

		if (countOfTasks == CONSTANTS::MAX_SIZE_TASKS) return;
		tasks[countOfTasks] = task;
		countOfTasks += 1;

	}

	void printExam() const
	{

		for (int i = 0; i < countOfTasks; i++)
		{

			tasks[i].printTask();

		}

	}

	void writeExamToFile(const char* fileName)
	{

		if (!fileName) return;

		std::ofstream file(fileName, std::ios::binary);

		if (!file.is_open()) return;

		file.write((const char*)&countOfTasks, sizeof(int));

		for (int i = 0; i < countOfTasks; i++)
		{

			tasks[i].writeToFile(file);

		}

		file.close();

	}

	Exam readExamFromFile(const char* fileName)
	{

		if (!fileName) return {};

		std::ifstream file(fileName, std::ios::binary);

		if (!file.is_open()) return {};

		Task fictiveTask;
		Exam result;
		file.read((char*)&result.countOfTasks, sizeof(int));

		for (int i = 0; i < result.countOfTasks; i++)
		{

			result.tasks[i] = fictiveTask.readFromFile(file);

		}

		file.close();
		return result;

	}

};

int main()
{

	Task task1("primer1", "PRIMER1", 30);
	Task task2("primer2", "PRIMER2", 15);
	Task task3("primer3", "ddada", 1111);
	//task1 = task2;
	//task1.printTask();

	Exam exam1;
	exam1.addTask(task1);
	exam1.addTask(task2);
	exam1.addTask(task3);
	exam1.printExam();
	exam1.writeExamToFile("../file.dat");
	std::cout << std::endl;

	Exam exam2 = exam1.readExamFromFile("../file.dat");
	exam2.printExam();

	return 0;

}
