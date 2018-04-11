#pragma once

#include "PhysicsActor.h"
#include <sf2d.h>
#include <stdio.h>

class CircleActor : public PhysicsActor {
private:
	float _radius;
	char _r;
	char _g;
	char _b;
public:
	CircleActor() { };
	CircleActor(vec2f position, float radius, float mass, float friction, float restitution, int color, bool isStatic);
	float GetRadius() { return _radius; }

	CollisionResult* CheckCollide_Circle(CircleActor* circle);
	CollisionResult* CheckCollide_Edge(EdgeActor* edge);
	CollisionResult* CheckCollide_BoundingBox(BoundingBox* bounds);
	bool CheckPointInCircle(vec2f point);

	void Render();
	void Print() { 
		printf("Position: (%.2f,%.2f)\n", _position.x, _position.y);
		printf("Velocity: (%.2f,%.2f)\n", _velocity.x, _velocity.y);
		printf("\x1b[0;0H");
	};
};