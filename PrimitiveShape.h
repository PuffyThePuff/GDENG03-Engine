#pragma once
#include "GraphicsEngine.h"

struct vec3
{
	float x, y, z;
};

struct vertex
{
	vec3 position;
	vec3 position1;
	vec3 color;
	vec3 color1;
};

class PrimitiveShape
{
public:
	PrimitiveShape();
	~PrimitiveShape();

	virtual void moveBy(vertex displacement);
	virtual vertex* getVertexList();
	virtual UINT getVertexSize();

private:
	UINT shapeIndex = 0;
};