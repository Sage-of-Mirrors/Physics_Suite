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
	~CircleActor() { delete _position; };
	CircleActor(vec2f*, float, float, char, char, char);
	void Render();
	void Print() { printf("Velocity: %f\n", _velocity->x); };
};