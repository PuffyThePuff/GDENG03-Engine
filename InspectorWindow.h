#pragma once
#include "AUIScreen.h"
#include "AGameObject.h"
#include "GameObjectManager.h"

class InspectorWindow: public AUIScreen
{
public:
	InspectorWindow(String name);
	~InspectorWindow();

	void drawUI() override;

private:
	void getObjectInfo(AGameObject* targetObject);

	bool isTargetObjectActive = true;
	float targetObjectPos[3] = {0.f, 0.f, 0.f};
	float targetObjectRot[3] = {0.f, 0.f, 0.f};
	float targetObjectScale[3] = {0.f, 0.f, 0.f};
};