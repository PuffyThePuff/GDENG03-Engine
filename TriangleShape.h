#pragma once
#include "PrimitiveShape.h"

class TriangleShape : public PrimitiveShape
{
public:
	TriangleShape(vertex origin, UINT index);
	~TriangleShape();

	void moveBy(vertex newPosition) override;
	vertex* getVertexList() override;
	UINT getVertexSize() override;

private:
	vertex list[3];
	UINT shapeIndex = 0;
};