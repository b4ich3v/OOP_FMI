#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

namespace HELPERS
{

	const int MAX_SIZE_BUFFER = 1024;
	const int SIZE_FOR_ID = 9;
	const char DATE_SEP = '-';
	const char DAY_SEP = ':';

	const int SIZE_FOR_DATE_FORMAT = 11;
	const int SIZE_FOR_YEAR_DATE_FORMAT = 5;
	const int SIZE_FOR_MONTH_DATE_FORMAT = 3;
	const int SIZE_FOR_DAY_DATE_FORMAT = 3;

	const int SIZE_FOR_DAY_FORMAT = 9;
	const int SIZE_FOR_HOURS_DAY_FORMAT = 3;
	const int SIZE_FOR_MINUTES_DAY_FORMAT = 3;
	const int SIZE_FOR_SECONDS_DAY_FORMAT = 3;

	int getCountOfLines(std::ifstream& file) 
	{

		int counter = 0;
		int currentPos = file.tellg();
		file.seekg(0, std::ios::beg);
		char buffer[MAX_SIZE_BUFFER];

		while (true) 
		{

			file.getline(buffer, MAX_SIZE_BUFFER);
			counter += 1;

			if (file.eof()) break;

		}

		file.clear();
		file.seekg(currentPos);

		return counter;

	}

	bool isDigit(char ch) 
	{

		return ch >= '0' && ch <= '9';

	}

	bool isUpper(char ch) 
	{

		return ch >= 'A' && ch <= 'Z';

	}

	bool isLower(char ch)
	{

		return ch >= 'a' && ch <= 'z';

	}

	bool isAlpha(char ch)
	{

		return isUpper(ch) || isLower(ch);

	}

}

struct TimeDateFormat
{
public:

	char data[HELPERS::SIZE_FOR_DATE_FORMAT] = "YYYY-MM-DD";

	void parse(std::ifstream& file) 
	{

		char bufferForYear[HELPERS::SIZE_FOR_YEAR_DATE_FORMAT];
		char bufferForMonth[HELPERS::SIZE_FOR_MONTH_DATE_FORMAT];
		char bufferForDay[HELPERS::SIZE_FOR_DAY_DATE_FORMAT];

		file.getline(bufferForYear, HELPERS::SIZE_FOR_YEAR_DATE_FORMAT, '-');
		file.getline(bufferForMonth, HELPERS::SIZE_FOR_MONTH_DATE_FORMAT, '-');
		file.getline(bufferForDay, HELPERS::SIZE_FOR_DAY_DATE_FORMAT, ' ');

		parseYear(bufferForYear);
		parseMonth(bufferForMonth);
		parseDay(bufferForDay);

		data[HELPERS::SIZE_FOR_DATE_FORMAT] = '\0';

	}

	void parseYear(const char* str) 
	{
		
		strncpy(data, str, strlen(str));

	}

	void parseMonth(const char* str) 
	{

		strncpy(data + HELPERS::SIZE_FOR_YEAR_DATE_FORMAT, str, strlen(str));

	}

	void parseDay(const char* str)
	{

		strncpy(data + HELPERS::SIZE_FOR_YEAR_DATE_FORMAT + HELPERS::SIZE_FOR_MONTH_DATE_FORMAT, str, strlen(str));

	}

	void printData() const
	{

		std::cout << data << " ";

	}

}; 

struct TimeDayFormat
{
public:

	char data[HELPERS::SIZE_FOR_DAY_FORMAT] = "HH:MM:SS";

	void parse(std::ifstream& file)
	{

		char bufferForHours[HELPERS::SIZE_FOR_HOURS_DAY_FORMAT];
		char bufferForMinutes[HELPERS::SIZE_FOR_MINUTES_DAY_FORMAT];
		char bufferForSeconds[HELPERS::SIZE_FOR_SECONDS_DAY_FORMAT];

		file.getline(bufferForHours, HELPERS::SIZE_FOR_HOURS_DAY_FORMAT, ':');
		file.getline(bufferForMinutes, HELPERS::SIZE_FOR_MINUTES_DAY_FORMAT, ':');
		file.getline(bufferForSeconds, HELPERS::SIZE_FOR_SECONDS_DAY_FORMAT, ';');

		parseHours(bufferForHours);
		parseMinutes(bufferForMinutes);
		parseSeconds(bufferForSeconds);

		data[HELPERS::SIZE_FOR_DAY_FORMAT] = '\0';

	}

	void parseHours(const char* str)
	{

		strncpy(data, str, strlen(str));

	}

	void parseMinutes(const char* str)
	{

		strncpy(data + HELPERS::SIZE_FOR_HOURS_DAY_FORMAT, str, strlen(str));

	}

	void parseSeconds(const char* str)
	{

		strncpy(data + HELPERS::SIZE_FOR_HOURS_DAY_FORMAT + HELPERS::SIZE_FOR_MINUTES_DAY_FORMAT, str, strlen(str));

	}

	void printData() const 
	{

		std::cout << data << " ";

	}

};

struct TimeStamp 
{
public:

	TimeDateFormat date;
	TimeDayFormat day;

};

class Analizator
{
private:

	char id[HELPERS::SIZE_FOR_ID];
	TimeStamp time;
	double temperature = 0;
	int humidity = 0;

	void parse(std::ifstream& file) 
	{

		file.getline(id, 9, ';');
		time.date.parse(file);
		time.day.parse(file);
		file >> temperature;
		file.ignore(1);
		file >> humidity;

	}

public:

	Analizator() = default;

	Analizator(std::ifstream& file) 
	{

		if (!file.is_open()) throw std::runtime_error("Error");
		parse(file);

	}

	void printData() const 
	{

		std::cout << id << " ";
		time.date.printData();
		time.day.printData();
		std::cout << temperature << " ";
		std::cout << humidity;

	}

	void writeToFile(std::ofstream& file) const
	{

		file << id << " ";
		file << "at ";
		file << time.date.data << " ";
		file << time.day.data << ": ";
		file << "Temp=";
		file << temperature << "°C, ";
		file << "Humidity=";
		file << humidity << "%" << std::endl;

	}

};

class ValidatorAndExecutor
{
private:

	std::ifstream& file;
	mutable bool validateLines[HELPERS::MAX_SIZE_BUFFER]{ true };

	bool validateId(const char* str) const 
	{

		if(strlen(str) < 4 || strlen(str) > 8 ) throw std::logic_error("Error with parsing id");

		for (int i = 0; i < strlen(str); i++)
		{

			if (!(HELPERS::isAlpha(str[i]) || HELPERS::isDigit(str[i])))
				throw std::logic_error("Error with parsing id");

		}

		return true;

	}

	bool validateTimestamp(const char* str) const
	{

		if (strlen(str) != 19) 
			throw std::logic_error("Error with parsing timestamp d");

		if(str[4] != HELPERS::DATE_SEP || str[7] != HELPERS::DATE_SEP ||
		   str[10] != ' ' || str[13] != HELPERS::DAY_SEP ||
		   str[16] != HELPERS::DAY_SEP) throw std::logic_error("Error with parsing timestamp");

		for (int i = 0; i < strlen(str); i++)
		{

			if (i == 4 || i == 7 || i == 10 || i == 13 || i == 16) continue;
			if (!HELPERS::isDigit(str[i])) throw std::logic_error("Error with parsing timestamp");

		}

		return true;

	}

	bool validateTemperature(const char* str) const
	{

		std::stringstream ss(str);
		double parsingNumber = 0;

		if (!(ss >> parsingNumber))
			throw std::logic_error("Temperature is not a valid number");

		if (parsingNumber < -50 || parsingNumber > 100)
			throw std::logic_error("Error with parsing temperature");

		return true;

	}

	bool validateHumidity(const char* str) const
	{

		std::stringstream ss(str);
		int parsingNumber = 0;

		if (!(ss >> parsingNumber))
			throw std::logic_error("Humidity is not a valid number");

		if (parsingNumber < 0 || parsingNumber > 100)
			throw std::logic_error("Error with parsing humidity");

		return true;

	}

public:

	ValidatorAndExecutor(std::ifstream& newFile): file(newFile) {}

	bool validation() const
	{

		char buffer[HELPERS::MAX_SIZE_BUFFER];
		int currentIndexLine = 0;

		while (file.peek() != EOF)
		{

			try
			{

				file.getline(buffer, HELPERS::MAX_SIZE_BUFFER, ';');
				validateId(buffer);

				char dateBuffer[HELPERS::MAX_SIZE_BUFFER];
				file.getline(dateBuffer, HELPERS::MAX_SIZE_BUFFER, ' ');

				char timeBuffer[HELPERS::MAX_SIZE_BUFFER];
				file.getline(timeBuffer, HELPERS::MAX_SIZE_BUFFER, ';');

				char timestamp[HELPERS::MAX_SIZE_BUFFER];
				snprintf(timestamp, HELPERS::MAX_SIZE_BUFFER, "%s %s", dateBuffer, timeBuffer);
				validateTimestamp(timestamp);

				file.getline(buffer, HELPERS::MAX_SIZE_BUFFER, ';');
				validateTemperature(buffer);

				file.getline(buffer, HELPERS::MAX_SIZE_BUFFER, '\n');
				validateHumidity(buffer);

			}
			catch (const std::exception&)
			{

				validateLines[currentIndexLine] = false;

			}

			currentIndexLine += 1;

		}

		return true;

	}

	void writeValidLines(const Analizator* anz, int count, std::ofstream& file) const 
	{

		for (int i = 0; i < count; i++)
		{

			if (validateLines[i]) anz[i].writeToFile(file);

		}

		file.close();

	}

};

int main() 
{

	std::ifstream file("file.txt");
	ValidatorAndExecutor VE(file);
	VE.validation();

	file.clear();
	file.seekg(0, std::ios::beg);

	int countOfData = HELPERS::getCountOfLines(file);
	Analizator* anz = new Analizator[countOfData];

	for (int i = 0; i < countOfData; i++)
	{

		anz[i] = Analizator(file);

	}

	for (int i = 0; i < countOfData; i++)
	{

		anz[i].printData();

	}

	std::cout << std::endl;
	std::ofstream result("result.txt");
	VE.writeValidLines(anz, countOfData, result);

	file.close();
	delete[] anz;
	return 0;

}
