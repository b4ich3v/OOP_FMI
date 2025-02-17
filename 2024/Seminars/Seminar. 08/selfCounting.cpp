#include "selfCounting.h"

unsigned SelfCounting::liveObjectsCount = 0;
unsigned SelfCounting::createdCount = 0;

SelfCounting::SelfCounting() : SelfCounting(42) {}

SelfCounting::SelfCounting(int value) : iterValue(value)
{

	liveObjectsCount++;
	createdCount++;

}

SelfCounting::SelfCounting(const SelfCounting& other) : iterValue(other.iterValue)
{

	liveObjectsCount++;
	createdCount++;

}

SelfCounting::~SelfCounting()
{

	liveObjectsCount--;

}

unsigned SelfCounting::getLiveObjectsCount()
{

	return liveObjectsCount;

}

unsigned SelfCounting::getCreatedCount()
{

	return createdCount;

}
