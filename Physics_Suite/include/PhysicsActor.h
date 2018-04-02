#pragma once
#include "vec2.h"
#include "framerate.h"

class PhysicsActor {
private:
	vec2f _position;
	float _angle;
	float _mass;
	
	vec2f _velocity;
	float _angular_velocity;
public:
	void Update();
	
	void ApplyForce(vec2f);	
	void ApplyAcceleration(Vec2f);
	void ApplyImpulse(vec2f);
	void ApplyVelocity(vec2f);
	
	void ApplyAngularVelocity(float);
	
	virtual void Render() = 0;
};