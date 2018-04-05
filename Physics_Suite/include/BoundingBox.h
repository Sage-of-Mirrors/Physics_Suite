#pragma once
#include "PhysicsActor.h"
#include <sf2d>

class BoundingBox : public PhysicsActor {
private:
	vec2f _min;
	vec2f _max;
	vec2f _size;
	vec2f _center;
	vec2f _halfwidths;
public:
	BoundingBox() { }
	BoundingBox(vec2f min, vec2f max) { _min = min; _max = max; }
	BoundingBox(vec2f* vecList, int count);
	
	CollisionResult* CheckCollide_Circle(CircleActor* circle);
	CollisionResult* CheckCollide_Edge(EdgeActor* edge);
	CollisionResult* CheckCollide_BoundingBox(BoundingBox* bounds);
	
	void Render();
};