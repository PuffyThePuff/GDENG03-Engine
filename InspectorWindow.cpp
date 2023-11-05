#include "InspectorWindow.h"

#include "MathUtils.h"

InspectorWindow::InspectorWindow(String name) : AUIScreen(name)
{

}

InspectorWindow::~InspectorWindow()
{

}

void InspectorWindow::drawUI()
{
	ImGuiWindowFlags windowFlags = 0;
	windowFlags |= ImGuiWindowFlags_NoResize;

	ImGui::Begin("Inspector Window", NULL, windowFlags);
	ImGui::SetWindowSize(ImVec2(300, 768 - 70));
	ImGui::SetWindowPos(ImVec2(1024 - 300, 20));

	if (!GameObjectManager::getInstance()->getSelectedObject())
	{
		ImGui::TextWrapped("No object selected. Select an object from the scene.");
	}

	else
	{
		AGameObject* selectedObject = GameObjectManager::getInstance()->getSelectedObject();
		getObjectInfo(selectedObject);

		ImGui::Text("Selected Object:");
		ImGui::SameLine();
		ImGui::Text(selectedObject->getName().c_str());
		ImGui::Separator();

		ImGui::Checkbox("Active", &isTargetObjectActive);
		ImGui::DragFloat3("Position", targetObjectPos, 1.f);
		ImGui::DragFloat3("Rotation", targetObjectRot, 1.f, -360.f, 360.f);
		ImGui::DragFloat3("Scale", targetObjectScale, 1.f, 0.f, 100.f);

		selectedObject->setActive(isTargetObjectActive);
		selectedObject->setScale(targetObjectScale[0], targetObjectScale[1], targetObjectScale[2]);
		selectedObject->setRotation(MathUtils::toRadians(targetObjectRot[0]), MathUtils::toRadians(targetObjectRot[1]), MathUtils::toRadians(targetObjectRot[2]));
		selectedObject->setPosition(targetObjectPos[0], targetObjectPos[1], targetObjectPos[2]);
	}

	ImGui::End();
}

void InspectorWindow::getObjectInfo(AGameObject* targetObject)
{
	isTargetObjectActive = targetObject->isActive();

	Vector3D pos = targetObject->getLocalPosition();
	targetObjectPos[0] = pos.x;
	targetObjectPos[1] = pos.y;
	targetObjectPos[2] = pos.z;

	Vector3D rot = targetObject->getLocalRotation();
	targetObjectRot[0] = MathUtils::toDegrees(rot.x);
	targetObjectRot[1] = MathUtils::toDegrees(rot.y);
	targetObjectRot[2] = MathUtils::toDegrees(rot.z);

	Vector3D scale = targetObject->getLocalScale();
	targetObjectScale[0] = scale.x;
	targetObjectScale[1] = scale.y;
	targetObjectScale[2] = scale.z;
}
