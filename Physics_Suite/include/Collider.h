#pragma once

#include "PhysicsActor.h"

class Collider {
private:
	Collider() { }
	static void Depenetration(CollisionResult* result);
	static void Repulsion(CollisionResult* result);
	
	static float Calc_Mu(PhysicsActor* first, PhysicsActor* second);
public:
	static void ProcessCollision(CollisionResult* result);
};