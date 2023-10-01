#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = nullptr;

void EngineTime::initialize()
{
	if (!sharedInstance)
	{
		sharedInstance = new EngineTime;
	}
}

double EngineTime::getDeltaTime()
{
	std::chrono::duration<double> delta = sharedInstance->start - sharedInstance->end;

	return delta.count();
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	sharedInstance->start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	sharedInstance->end = sharedInstance->start;
}