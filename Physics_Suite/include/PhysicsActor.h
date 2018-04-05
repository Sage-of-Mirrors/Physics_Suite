#pragma once
#include "vec2.h"
#include "framerate.h"
#include "CollisionResult.h"
#include <stdio.h>
#include <assert.h>

class CircleActor;
class EdgeActor;
class BoundingBox;

enum PhysicsType {
	CIRCLE,
	EDGE,
	BOUNDING_BOX,
	NONE
};

class PhysicsActor {
protected:
	vec2f _position;
	float _angle;
	float _mass;
	
	vec2f _velocity;
	float _angular_velocity;
	PhysicsType _type;
public:
	void ApplyForce(vec2f& force);
	void ApplyAcceleration(vec2f& acceleration);
	void ApplyImpulse(vec2f& impulse);
	void ApplyVelocity(vec2f& velocity_change);
	void ApplyAngularVelocity(float angular_velocity_change);

	vec2f GetPosition() { return _position; }
	PhysicsType GetType() { return _type; }
	CollisionResult* CheckCollide(PhysicsActor* actor);
	virtual CollisionResult* CheckCollide_Circle(CircleActor* circle) = 0;
	virtual CollisionResult* CheckCollide_Edge(EdgeActor* edge) = 0;
	virtual CollisionResult* CheckCollide_BoundingBox(BoundingBox* bounds) = 0;
	
	void Update();
	virtual void Render() = 0;

	virtual ~PhysicsActor() { }
};