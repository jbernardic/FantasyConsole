 #pragma once

#include "Shape.h"

struct DrawablePolygonShape {
	const VertexArray& va;
};
class PolygonShape : public Shape{
public:
	PolygonShape(float radius = 100.0f, unsigned int numberOfPoints = 100, float x = 0.0f, float y = 0.0f);
	 const VertexArray& GetVertexArray() const{ return m_VA; };
	 unsigned int GetID() const{return m_VA.GetRendID();}
	 unsigned int GetPointNumber() const{return m_PointNumber;}
private:
	unsigned int m_PointNumber;
	float m_Radius;
	VertexArray m_VA;
	std::shared_ptr<VertexBuffer> m_VB;
};
