#pragma once
#include "vec2.h"
#include "array.h"

struct CollisionResult {
public:
	vec2f Normal;
	CArrayT<vec2f> Points;
};