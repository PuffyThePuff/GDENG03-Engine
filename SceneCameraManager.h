#pragma once
#include "Camera.h"

class SceneCameraManager
{
public:
	static SceneCameraManager* getInstance();
	static void destroy();

	void setSceneCamera(Camera* scene_camera);
	void update();

	Matrix4x4 getSceneCameraViewMatrix();

private:
	SceneCameraManager();
	~SceneCameraManager();
	SceneCameraManager(SceneCameraManager const&) {};
	SceneCameraManager& operator =(SceneCameraManager const&) {};
	static SceneCameraManager* instance;

	Camera* mSceneCamera = nullptr;
};