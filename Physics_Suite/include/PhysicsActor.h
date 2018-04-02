#pragma once
#include "vec2.h"

class PhysicsActor {
private:
	vec2f _position;
	float _angle;
	float _mass;
	
	vec2f _velocity;
	float _angular_velocity;
public:
	void Update(float);
	void ApplyForce(vec2f, float);	
	void ApplyAcceleration(Vec2f, float);
	void ApplyImpulse(vec2f);
	void ApplyVelocity(vec2f);
	virtual void Render() = 0;
};