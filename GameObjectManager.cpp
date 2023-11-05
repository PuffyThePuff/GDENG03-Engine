#include "GameObjectManager.h"
#include "EngineTime.h"
#include "Cube.h"
#include "Plane.h"
#include <iostream>

GameObjectManager* GameObjectManager::instance = nullptr;

GameObjectManager* GameObjectManager::getInstance()
{
	return instance;
}

void GameObjectManager::initialize()
{
	instance = new GameObjectManager();
}

void GameObjectManager::destroy()
{
	instance->gameObjectTable.clear();

	for (auto& i : instance->gameObjectList)
	{
		delete i;
	}
}

AGameObject* GameObjectManager::findObjectByName(std::string name)
{
	return gameObjectTable[name];
}

std::vector<AGameObject*> GameObjectManager::getAllGameObjects()
{
	return gameObjectList;
}

int GameObjectManager::getObjectCount()
{
	return gameObjectList.size();
}

int GameObjectManager::getActiveObjectCount()
{
	int activeObjectCount = 0;
	for (auto& i : gameObjectList)
	{
		if (i->isActive()) activeObjectCount++;
	}
	return activeObjectCount;
}

void GameObjectManager::update()
{
	for (auto& i : gameObjectList)
	{
		if (i->isActive())
		{
			i->update(EngineTime::getDeltaTime());
		}
	}
}

void GameObjectManager::render(int viewport_width, int viewport_height, VertexShader* vertex_shader, PixelShader* pixel_shader)
{
	for (auto& i : gameObjectList)
	{
		if (i->isActive())
		{
			i->draw(viewport_width, viewport_height, vertex_shader, pixel_shader);
		}
	}
}

void GameObjectManager::addObject(AGameObject* game_object)
{
	gameObjectList.push_back(game_object);
	gameObjectTable[game_object->getName()] = game_object;
}

void GameObjectManager::createObject(PrimitiveType primitive_type, void* shader_byte_code, size_t shader_size)
{
	std::string newName = "";

	switch (primitive_type)			//got the do-while loop idea from Nate
	{
		case CUBE:
			{
				int cubeCount = -1;
				AGameObject* cube = nullptr;
				do
				{
					cubeCount++;
					newName = "Cube " + std::to_string(cubeCount);
					cube = gameObjectTable[newName];
				}
				while (cube);

				Cube* newCube = new Cube(newName, shader_byte_code, shader_size);
				addObject(newCube);
				std::cout << newCube->getName() << " instantiated." << std::endl;
				break;
			}
		case PLANE:
			{
				int planeCount = -1;
				AGameObject* plane = nullptr;
				do
				{
					planeCount++;
					newName = "Plane " + std::to_string(planeCount);
					plane = gameObjectTable[newName];
				}
				while (plane);

				Plane* newPlane = new Plane(newName, shader_byte_code, shader_size);
				addObject(newPlane);
				std::cout << newPlane->getName() << " instantiated." << std::endl;

				break;
			}
		default:
			break;
	}
}

void GameObjectManager::createObject(PrimitiveType primitive_type)
{
	std::string newName = "";

	switch (primitive_type)
	{
		case CUBE:
			{
				int cubeCount = -1;
				AGameObject* cube = nullptr;
				do
				{
					cubeCount++;
					newName = "Cube " + std::to_string(cubeCount);
					cube = gameObjectTable[newName];
				}
				while (cube);

				Cube* newCube = new Cube(newName, vertexShaderByteCode, shaderSize);
				addObject(newCube);
				std::cout << newCube->getName() << " instantiated." << std::endl;
			
				break;
			}
		case PLANE:
			{
				int planeCount = -1;
				AGameObject* plane = nullptr;
				do {
					planeCount++;
					newName = "Plane " + std::to_string(planeCount);
					plane = gameObjectTable[newName];
				}
				while (plane);

				Plane* newPlane = new Plane(newName, vertexShaderByteCode, shaderSize);
				addObject(newPlane);
				std::cout << newPlane->getName() << " instantiated." << std::endl;

				break;
			}
		default:
			break;
	}
}

void GameObjectManager::deleteObject(AGameObject* game_object)
{
	std::string key = game_object->getName();

	gameObjectTable.erase(key);
	gameObjectList.erase(std::remove(gameObjectList.begin(), gameObjectList.end(), game_object), gameObjectList.end());
	gameObjectList.shrink_to_fit();

	delete game_object;
}

void GameObjectManager::deleteObjectByName(std::string name)
{
	AGameObject* object = findObjectByName(name);

	if (object)
	{
		deleteObject(object);
	}
}

void GameObjectManager::setSelectedObject(std::string name)
{
	if (selectedObject)
	{
		selectedObject->deselectObject();
	}

	AGameObject* object = findObjectByName(name);

	if (object)
	{
		selectedObject = object;
		object->selectObject();
	}
}

void GameObjectManager::setSelectedObject(AGameObject* game_object)
{
	if (selectedObject)
	{
		selectedObject->deselectObject();
	}

	selectedObject = game_object;
	game_object->selectObject();
}

AGameObject* GameObjectManager::getSelectedObject()
{
	return selectedObject;
}

void GameObjectManager::deselectObject()
{
	if (selectedObject)
	{
		selectedObject->deselectObject();
		selectedObject = nullptr;
	}
}

void GameObjectManager::setVertexShaderProperties(void* shader_byte_code, size_t shader_size)
{
	vertexShaderByteCode = shader_byte_code;
	shaderSize = shader_size;
}

GameObjectManager::GameObjectManager()
{
	selectedObject = nullptr;
}

GameObjectManager::~GameObjectManager()
{
	delete instance;
}