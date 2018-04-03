#pragma once

#include "PhysicsActor.h"
#include "CircleActor.h"

class Collider {
public:
	static bool CheckCollision_Circle_Circle(CircleActor*, CircleActor*);
};