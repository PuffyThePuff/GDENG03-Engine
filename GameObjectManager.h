#pragma once
#include "AGameObject.h"
#include <string>
#include <vector>
#include <unordered_map>
#include "VertexShader.h"
#include "PixelShader.h"

class GameObjectManager
{
public:
	enum PrimitiveType {
		CUBE,
		PLANE
	};

	static GameObjectManager* getInstance();
	static void initialize();
	static void destroy();

	AGameObject* findObjectByName(std::string name);
	std::vector<AGameObject*> getAllGameObjects();
	int getObjectCount();
	int getActiveObjectCount();
	void update();
	void render(int viewport_width, int viewport_height, VertexShader* vertex_shader, PixelShader* pixel_shader);
	void addObject(AGameObject* game_object);
	void createObject(PrimitiveType primitive_type, void* shader_byte_code, size_t shader_size);
	void createObject(PrimitiveType primitive_type);
	void deleteObject(AGameObject* game_object);
	void deleteObjectByName(std::string name);

	//let object manager handle the selection to lessen spaghetti code
	void setSelectedObject(std::string name);
	void setSelectedObject(AGameObject* game_object);
	AGameObject* getSelectedObject();
	void deselectObject();

	void setVertexShaderProperties(void* shader_byte_code, size_t shader_size);

private:
	GameObjectManager();
	~GameObjectManager();
	GameObjectManager(GameObjectManager const&) {};
	GameObjectManager& operator =(GameObjectManager const&) {};
	static GameObjectManager* instance;

	std::vector<AGameObject*> gameObjectList;
	std::unordered_map<std::string, AGameObject*> gameObjectTable;

	AGameObject* selectedObject = nullptr;

	void* vertexShaderByteCode = nullptr;
	size_t shaderSize = 0;
};