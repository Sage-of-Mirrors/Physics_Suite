#pragma once
#include "vec2.h"
#include "framerate.h"

class PhysicsActor {
protected:
	vec2f _position;
	float _angle;
	float _mass;
	
	vec2f _velocity;
	float _angular_velocity;
public:
	void Update();
	
	void ApplyForce(vec2f&);
	void ApplyAcceleration(vec2f&);
	void ApplyImpulse(vec2f&);
	void ApplyVelocity(vec2f&);
	
	void ApplyAngularVelocity(float);
	
	virtual void Render() = 0;
};