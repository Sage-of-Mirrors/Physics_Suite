#pragma once
#include "PhysicsActor.h"
#include <math.h>
#include <sf2d.h>
#include <float.h>

class EdgeActor : public PhysicsActor {
private:
	vec2f _startPoint;
	vec2f _endPoint;
	vec2f _normal;

	float _width;
	char _r;
	char _g;
	char _b;
public:
	EdgeActor();
	~EdgeActor();

	vec2f GetStartPoint() { return _startPoint; }
	vec2f GetEndPoint() { return _endPoint; }
	vec2f GetNormal() { return _normal; }

	bool CheckCollide_Circle(CircleActor* circle);
	bool CheckCollide_Edge(EdgeActor* edge);
	bool CheckCollide_BoundingBox(BoundingBox* edge);
	bool CheckPointOnEdge(vec2f point);

	void Render();
};