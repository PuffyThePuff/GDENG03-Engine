#include "SceneOutliner.h"

SceneOutliner::SceneOutliner(String name) : AUIScreen(name)
{

}

SceneOutliner::~SceneOutliner()
{

}

void SceneOutliner::drawUI()
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Scene Outliner", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, 700));
	ImGui::SetWindowPos(ImVec2(1024 - 600, 20));

	std::vector<AGameObject*> objectList = GameObjectManager::getInstance()->getAllGameObjects();
	for (auto& i : objectList)
	{
		if (i == GameObjectManager::getInstance()->getSelectedObject())
		{
			if (ImGui::Button(i->getName().c_str(), ImVec2(300, 25)))
			{
				GameObjectManager::getInstance()->deselectObject();
			}
		}

		else
		{
			if (ImGui::Button(i->getName().c_str(), ImVec2(300, 25)))
			{
				GameObjectManager::getInstance()->setSelectedObject(i);
			}
		}
	}

	ImGui::End();
}