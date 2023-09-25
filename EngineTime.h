#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class Window;

class EngineTime
{
public:
	void initialize();
	double getDeltaTime();

private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator= (EngineTime const&){};

	static EngineTime* sharedInstance;

	std::chrono::system_clock::time_point start;
	std::chrono::system_clock::time_point end;

	double deltaTime = 0.0;

	void LogFrameStart();
	void LogFrameEnd();

	friend class Window;
};