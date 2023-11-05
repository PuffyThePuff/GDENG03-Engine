#pragma once
#include "AUIScreen.h"
#include "GameObjectManager.h"

class SceneOutliner : public AUIScreen
{
public:
	SceneOutliner(String name);
	~SceneOutliner();

	void drawUI() override;
};