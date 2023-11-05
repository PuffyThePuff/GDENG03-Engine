#pragma once
#include "AUIScreen.h"

class Profiler: public AUIScreen
{
public:
	Profiler(String name);
	~Profiler();

	void drawUI() override;

private:
	//TODO: name these better this makes no sense lmao
	float deltaTime = 0.f;
	float ticks = 0.f;
	float averageFrameTime = 0.f;
	float framesPerSec = 0.f;
	float frameTime = 0.f;
};