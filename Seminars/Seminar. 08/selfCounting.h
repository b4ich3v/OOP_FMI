#pragma once

class SelfCounting
{

	const int iterValue;

	static unsigned liveObjectsCount;
	static unsigned createdCount;

public:

	SelfCounting();
	SelfCounting(int value);
	SelfCounting(const SelfCounting& other);
	~SelfCounting();

	static unsigned getLiveObjectsCount();
	static unsigned getCreatedCount();

};
