#include <iostream>
#include <fstream>
#include <cstring>

namespace HELPERS
{

	const char PATTERN1[14] = "Welcome back ";
	const char PATTERN2[12] = "HAVE FUN!!!";
	const int MAX_SIZE_ATRR = 129;
	const int MAX_COUNT_USERS = 100;
	const int MAX_SIZE_ROW = 1024;

}

enum class Message
{

	DID_NOT_FOUND_NAME = 0,
	FOUND_NAME = 1,
	FULL_DATA = 2

};

struct Error
{

	bool result;
	Message message;

};

struct User
{
public:

	char name[HELPERS::MAX_SIZE_ATRR];
	char email[HELPERS::MAX_SIZE_ATRR];
	char password[HELPERS::MAX_SIZE_ATRR];

};

struct System
{
public:

	User users[HELPERS::MAX_COUNT_USERS];
	int countOfUsers = 0;

	char allNames[HELPERS::MAX_COUNT_USERS][HELPERS::MAX_SIZE_ATRR];
	int lastUsedIndex = 0;

};

Error isNameReserved(const char* name, const System& system)
{

	if (system.lastUsedIndex == HELPERS::MAX_COUNT_USERS) return { false, Message::FULL_DATA };

	for (int i = 0; i < HELPERS::MAX_COUNT_USERS; i++)
	{

		if (!strcmp(system.allNames[i], name)) return { true, Message::FOUND_NAME };

	}

	return { false, Message::DID_NOT_FOUND_NAME };

}

void printUser(const User& user)
{

	std::cout << HELPERS::PATTERN1 << user.name << std::endl;
	std::cout << HELPERS::PATTERN2 << std::endl;


}

void registerUser(const char* name, const char* email, const char* password, System& system, bool& status)
{

	Error error = isNameReserved(name, system);

	if (!error.result && (int)error.message == (int)Message::DID_NOT_FOUND_NAME)
	{

		User newUser;

		strncpy(newUser.name, name, strlen(name));
		newUser.name[strlen(name)] = '\0';
		strncpy(system.allNames[system.lastUsedIndex], name, strlen(name));
		system.allNames[system.lastUsedIndex][strlen(name)] = '\0';
		system.lastUsedIndex += 1;

		strncpy(newUser.email, email, strlen(email));
		newUser.email[strlen(email)] = '\0';

		strncpy(newUser.password, password, strlen(password));
		newUser.password[strlen(password)] = '\0';

		system.users[system.countOfUsers] = newUser;
		system.countOfUsers += 1;

		status = true;

	}
	else if (!error.result && (int)error.message == (int)Message::DID_NOT_FOUND_NAME)
	{

		std::cout << "The System is full!" << std::endl;
		status = false;

	}
	else
	{

		std::cout << "This name already exist in the system!" << std::endl;
		status = false;

	}

}

void loginUser(const char* name, const char* password, const System& system, bool& status, int& userIndex)
{

	for (int i = 0; i < system.countOfUsers; i++)
	{

		if (!strcmp(system.users[i].name, name) && !strcmp(system.users[i].password, password))
		{

			userIndex = i;
			status = true;
			return;

		}

	}

	status = false;

}

void writeUserToFile(const User& user, std::ofstream& file)
{

	file << user.name << " ";
	file << user.email << " ";
	file << user.password << " ";
	file << std::endl;

}

void writeDataBaseForNames(std::ofstream& file, const char allNames[100][129], int size)
{

	file << size << std::endl;

	for (int i = 0; i < size; i++)
	{

		file << allNames[i] << std::endl;

	}

}

void writeSystemToFile(const System& system, const char* fileName, const char* dataBaseForNames)
{

	std::ofstream file1(fileName, std::ios::trunc);
	std::ofstream file2(dataBaseForNames, std::ios::trunc);

	if (!file1.is_open() || !file2.is_open()) return;

	writeDataBaseForNames(file2, system.allNames, system.lastUsedIndex);

	file1 << system.countOfUsers << std::endl;

	for (int i = 0; i < system.countOfUsers; i++)
	{

		writeUserToFile(system.users[i], file1);

	}

	file1.close();
	file2.close();

}

void readDataBaseForNames(std::ifstream& file, System& system)
{

	file >> system.lastUsedIndex;
	file.ignore(1);

	char buffer[HELPERS::MAX_SIZE_ROW];

	for (int i = 0; i < system.lastUsedIndex; i++)
	{

		file.getline(buffer, HELPERS::MAX_SIZE_ROW);
		strncpy(system.allNames[i], buffer, HELPERS::MAX_SIZE_ROW);
		system.allNames[i][strlen(buffer)] = '\0';

	}

}

User readUserFromFile(std::ifstream& file)
{

	User result;

	file >> result.name;
	file >> result.email;
	file >> result.password;
	file.ignore(1);

	return result;

}

System readSystemFromFile(const char* fileName, const char* dataBaseForNames)
{

	std::ifstream file1(fileName);
	std::ifstream file2(dataBaseForNames);

	if (!file1.is_open() || !file2.is_open()) return {};

	System result;

	file1 >> result.countOfUsers;
	file1.ignore(1);

	for (int i = 0; i < result.countOfUsers - 2; i++)
	{

		result.users[i] = readUserFromFile(file1);

	}

	file1.close();
	file2.close();
	return result;

}

int main()
{

	//System system = readSystemFromFile("../test1.txt", "../test2.txt");
	System system;
	bool atleastOneCommand = false;

	while (true)
	{

		std::cout << "Enter a command: " << std::endl;

		char choice[HELPERS::MAX_SIZE_ATRR];
		std::cin.getline(choice, HELPERS::MAX_SIZE_ATRR);

		if (!strcmp("register", choice))
		{

			bool status = true;
			atleastOneCommand = true;

			char name[HELPERS::MAX_SIZE_ATRR];
			char email[HELPERS::MAX_SIZE_ATRR];
			char password[HELPERS::MAX_SIZE_ATRR];

			std::cin.getline(name, HELPERS::MAX_SIZE_ATRR);
			std::cin.getline(email, HELPERS::MAX_SIZE_ATRR);
			std::cin.getline(password, HELPERS::MAX_SIZE_ATRR);

			registerUser(name, email, password, system, status);

			if (!status)
			{

				std::cout << "Try a new name!" << std::endl;

			}
			else
			{

				std::cout << "Successfull registration!" << std::endl;

			}

		}
		else if (!strcmp("login", choice))
		{

			bool status = true;
			atleastOneCommand = true;
			int userIndex = 0;

			char name[HELPERS::MAX_SIZE_ATRR];
			char password[HELPERS::MAX_SIZE_ATRR];

			std::cin.getline(name, HELPERS::MAX_SIZE_ATRR);
			std::cin.getline(password, HELPERS::MAX_SIZE_ATRR);

			loginUser(name, password, system, status, userIndex);

			if (!status)
			{

				std::cout << "Incorrect name or password, try again!" << std::endl;

			}
			else
			{

				std::cout << "Successfull login!" << std::endl;
				printUser(system.users[userIndex]);

			}

		}
		else if (!strcmp("exit", choice))
		{

			break;

		}
		else
		{

			std::cout << "Unknown command!" << std::endl;

		}

		std::cout << std::endl;

	}

	if (!atleastOneCommand)
	{

		system.lastUsedIndex = 0;
		system.countOfUsers = 0;

	}

	writeSystemToFile(system, "../test1.txt", "../test2.txt");

	return 0;

}

