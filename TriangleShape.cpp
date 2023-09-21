#include "TriangleShape.h"

// create triangle at origin x, y, z
TriangleShape::TriangleShape(vertex origin, UINT index):shapeIndex(index)
{
	list[0] = origin;

	list[1].position.x = origin.position.x + 0.5;
	list[1].position.y = origin.position.y + 1;
	list[1].position.z = 0;

	list[2].position.x = origin.position.x + 1;
	list[2].position.y = origin.position.y;
	list[2].position.z = 0;
}

TriangleShape::~TriangleShape()
{
}

void TriangleShape::moveBy(vertex newPosition)
{
	for (auto& i : list)
	{
		i.position.x = newPosition.position.x;
		i.position.y = newPosition.position.y;
		i.position.z = newPosition.position.z;
	}

	//list[0].position.x = newPosition.position.x;
	//list[0].position.y = newPosition.position.y;
	//list[0].position.z = newPosition.position.z;

	//list[1].position.x = newPosition.position.x;
	//list[1].position.y = newPosition.position.y;
	//list[1].position.z = newPosition.position.z;

	//list[2].position.x = newPosition.position.x;
	//list[2].position.y = newPosition.position.y;
	//list[2].position.z = newPosition.position.z;
}

vertex* TriangleShape::getVertexList()
{
	return list;
}

UINT TriangleShape::getVertexSize()
{
	return ARRAYSIZE(list);
}
