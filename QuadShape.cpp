#include "QuadShape.h"

QuadShape::QuadShape(vertex origin, UINT index):shapeIndex(index)
{
	list[0] = origin;

	list[1].position.x = origin.position.x;
	list[1].position.y = origin.position.y + 1;
	list[1].position.z = origin.position.z;

	list[2].position.x = origin.position.x + 1;
	list[2].position.y = origin.position.y + 1;
	list[2].position.z = origin.position.z;

	list[3].position.x = origin.position.x + 1;
	list[3].position.y = origin.position.y;
	list[3].position.z = origin.position.z;

	list[4] = origin;
}

QuadShape::~QuadShape()
{
}

void QuadShape::moveBy(vertex newPosition)
{
	for (auto& i : list)
	{
		i.position.x = newPosition.position.x;
		i.position.y = newPosition.position.y;
		i.position.z = newPosition.position.z;
	}
}

vertex* QuadShape::getVertexList()
{
	return list;
}

UINT QuadShape::getVertexSize()
{
	return ARRAYSIZE(list);
}
