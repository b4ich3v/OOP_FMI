#include "Logger.h"

int main() 
{

	Logger& loggerDummy = Logger::createAndGetAddress();
	Logger& logger1 = Logger::createAndGetAddress();
	Logger& logger2 = Logger::createAndGetAddress();

	std::cout << loggerDummy.getLastLoggedMessage() << std::endl;
	logger1.logMessage("Message 1");
	std::cout << loggerDummy.getLastLoggedMessage() << std::endl;
	logger2.logMessage("Message 2");
	std::cout << loggerDummy.getLastLoggedMessage() << std::endl;

	if (logger1 == logger2) 
	{

		std::cout << "This proves that it is one instance!" << std::endl;

	}

	return 0;

}
