#include "CommunicationPipe.h"

void CommunicationPipe::addSharedPtr()
{

	countOfSharedPtrs += 1;
	if (countOfSharedPtrs == 1) countOfWeakPtrs += 1;

}

void CommunicationPipe::removeSharedPtr()
{

	countOfSharedPtrs -= 1;
	if (countOfSharedPtrs == 0) countOfWeakPtrs -= 1;

}

void CommunicationPipe::addWeakPtr()
{

	countOfWeakPtrs += 1;

}

void CommunicationPipe::removeWeakPtr()
{

	countOfWeakPtrs -= 1;

}

bool CommunicationPipe::noOwners() const
{

	return countOfSharedPtrs == 0;

}

bool CommunicationPipe::noVisitors() const
{

	return countOfWeakPtrs == 0;

}

size_t CommunicationPipe::getCountOfSharedPtrs() const
{

	return countOfSharedPtrs;

}

size_t CommunicationPipe::getCountOfWeakPtrs() const
{

	return countOfWeakPtrs;

}
