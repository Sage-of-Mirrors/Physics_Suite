#pragma once
#include "vec2.h"
#include "array.h"

struct CollisionResult {
public:
	// Objects involved in the collision
	PhysicsActor* Obj1;
	PhysicsActor* Obj2;
	
	// Collision normal
	vec2f Normal;
	// Collision tangent
	vec2f Tangent;
	// List of points where the objects collided
	vec2f Point;
	
	// Distance the objects must travel to be separated
	float DepenetrationDistance;
	
	float Friction;
	float Restitution;
	
	float MixFriction(float f1, float f2) { return sqrt(f1 + f2); }
	float MixRestitution(float f1, float f2) { return f1 > f2 ? f1 : f2 }
};