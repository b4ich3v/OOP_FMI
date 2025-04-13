#include <iostream>
#include <cstring>
#pragma once

const int MAX_SIZE_MESSAGE = 100;

class Logger
{
private:

	char lastLoggedMessage[MAX_SIZE_MESSAGE + 1] = "default message";

	Logger() = default;

public:

	Logger(const Logger& other) = delete;

	Logger& operator = (const Logger& other) = delete;

	static Logger& createAndGetAddress();

	const char* getLastLoggedMessage() const;

	friend bool operator == (const Logger& l1, const Logger& l2);

	void logMessage(const char* message);

};

