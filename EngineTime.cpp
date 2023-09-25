#include "EngineTime.h"

void EngineTime::initialize()
{
	start = std::chrono::system_clock::now();

	deltaTime = 0.0;
}

double EngineTime::getDeltaTime()
{
	return deltaTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
	start = std::chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
	end = std::chrono::system_clock::now();

	auto elapsedTime = std::chrono::duration_cast<std::chrono::microseconds>(end - start);


}