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
	CircleActor(vec2f, float, float, char, char, char);
	float GetRadius() { return _radius; }

	bool CheckCollide_Circle(CircleActor* circle);
	bool CheckCollide_Edge(EdgeActor* edge);
	bool CheckCollide_BoundingBox(BoundingBox* bounds);

	void Render();
	void Print() { 
		printf("Position: (%.2f,%.2f)\n", _position.x, _position.y);
		printf("Velocity: (%.2f,%.2f)\n", _velocity.x, _velocity.y);
		printf("\x1b[0;0H");
	};
};