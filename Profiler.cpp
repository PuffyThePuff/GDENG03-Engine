#include "Profiler.h"
#include "EngineTime.h"

Profiler::Profiler(String name) : AUIScreen(name)
{

}

Profiler::~Profiler()
{

}

void Profiler::drawUI()
{
	frameTime += 1.f;
	ticks += EngineTime::getDeltaTime();
	deltaTime += EngineTime::getDeltaTime();

	if (frameTime >= 1.f)
	{
		averageFrameTime = ticks / frameTime;
		framesPerSec = 1.f / averageFrameTime;
		frameTime = 0.f;
		ticks = 0.f;
	}

	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Engine Profiler", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(400, 70));
	ImGui::SetWindowPos(ImVec2(10, 600));

	ImGui::Text("Frame time: ");
	ImGui::SameLine();
	ImGui::Text(std::to_string(averageFrameTime * 1000.f).c_str());
	ImGui::SameLine();
	ImGui::Text(" ms");

	ImGui::Text("FPS: ");
	ImGui::SameLine();
	ImGui::Text(std::to_string(framesPerSec).c_str());
	
	ImGui::End();
}