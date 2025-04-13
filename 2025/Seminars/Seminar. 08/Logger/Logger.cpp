#include "Logger.h"

Logger& Logger::createAndGetAddress()
{

	static Logger result;
	return result;

}

void Logger::logMessage(const char* message) 
{

	Logger& ref = createAndGetAddress();
	strncpy(ref.lastLoggedMessage, message, strlen(message));
	ref.lastLoggedMessage[strlen(message)] = '\0';

	std::cout << message << std::endl;

}

const char* Logger::getLastLoggedMessage() const 
{

	return lastLoggedMessage;

}

bool operator == (const Logger& l1, const Logger& l2)
{

	return &l1 == &l2;

}
