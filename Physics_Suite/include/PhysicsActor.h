#pragma once
#include "vec2.h"

class PhysicsActor {
private:
	vec2f _position;
	vec2f _velocity;
	vec2f _momentum;
	vec2f _force;
	float _mass;
public:
	void Update(float);
	virtual void Render() = 0;
};