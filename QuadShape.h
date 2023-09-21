#pragma once
#include "PrimitiveShape.h"

class QuadShape : public PrimitiveShape
{
public:
	QuadShape(vertex origin, UINT index);
	~QuadShape();
	
	void moveBy(vertex newPosition) override;
	vertex* getVertexList() override;
	UINT getVertexSize() override;

private:
	vertex list[5];
	UINT shapeIndex = 0;
};