#include "..\..\include\physics\EdgeActor.h"
#include "..\..\include\physics\CircleActor.h"

EdgeActor::EdgeActor(vec2f startPos, vec2f endPos, float mass, float friction, float restitution, float width, bool isStatic, char r, char g, char b) {
	_startPoint = startPos;
	_endPoint = endPos;
	_mass = mass;
	_friction = friction;
	_restitution = restitution;
	_width = width;
	_static = isStatic;
	_r = r;
	_g = g;
	_b = b;
}

void EdgeActor::SetColor(char r, char g, char b) {
	_r = r;
	_g = g;
	_b = b;
}

void EdgeActor::Render() {
	sf2d_draw_line(_startPoint.x + _position.x, _startPoint.y + _position.y,
		_endPoint.x + _position.x, _endPoint.y + _position.y,
		_width, RGBA8(_r, _g, _b, 0xFF));
}

CollisionResult* EdgeActor::CheckCollide_Circle(CircleActor* circle) {
	CollisionResult* result = new CollisionResult();
	result->Obj1 = this;
	result->Obj2 = circle;
	result->Friction = result->MixFriction(_friction, circle->GetFriction());
	result->Restitution = result->MixRestitution(_restitution, circle->GetRestitution());

	vec2f circPos = circle->GetPosition();
	float circRadius = circle->GetRadius();
	vec2f realStart = _startPoint + _position;
	vec2f realEnd = _endPoint + _position;

	bool startIn = circle->CheckPointInCircle(realStart);
	bool endIn = circle->CheckPointInCircle(realEnd);

	if (startIn || endIn) {
		vec2f point;

		if (startIn)
			point = realStart;
		else
			point = realEnd;

		result->Point = point;

		vec2f pointToCenterDist = (circPos - point);
		result->DepenetrationDistance = circRadius - pointToCenterDist.length();
		result->Normal = pointToCenterDist.normalize();
		result->Tangent = result->Normal.perpendicular();

		return result;
	}

	float lineLength = (realEnd - realStart).length();

	float dot = (((circPos.x - realStart.x) * (realEnd.x - realStart.x)) + ((circPos.y - realStart.y) * (realEnd.y - realStart.y))) / pow(lineLength, 2);

	vec2f closestPoint = vec2f(realStart.x + (dot * (realEnd.x - realStart.x)), realStart.y + (dot * (realEnd.y - realStart.y)));

	if (!CheckPointOnEdge(closestPoint) || !circle->CheckPointInCircle(closestPoint))
	{
		delete result;
		return nullptr;
	}

	result->Point = closestPoint;

	vec2f pointToCenterDist = (closestPoint - circPos);
	result->DepenetrationDistance = circRadius - pointToCenterDist.length();
	result->Normal = pointToCenterDist.normalize();
	result->Tangent = result->Normal.perpendicular();

	return result;
}

/*
CollisionResult* EdgeActor::CheckCollide_Circle(CircleActor* circle) {
	// First, we calculate a, b, and c for the equation that describes the intersection between a line and a circle:
	// a^2 * u + b * u + c
	vec2f circPos = circle->GetPosition();
	float circRadius = circle->GetRadius();

	vec2f realStart = _startPoint + _position;
	vec2f realEnd = _endPoint + _position;

	float dx = realEnd.x - realStart.x;
	float dy = realEnd.y - realStart.y;

	float a = (dx) * (dx) +
			  (dy) * (dy);

	float b = 2 * 
		      (dx * (realStart.x - circPos.x) +
			   dy * (realStart.y - circPos.y));

	float c = ((realStart.x - circPos.x) * (realStart.x - circPos.x)) +
		      ((realStart.y - circPos.y) * (realStart.y - circPos.y)) -
		      (circRadius * circRadius);

	float delta = (b * b) - 4 * a * c;

	// There are no solutions to the intersection equation, so there is no intersection.
	if (a <= FLT_EPSILON || delta < FLT_EPSILON)
		return nullptr;
	
	// Calculate where the first point of intersection is
	float u1 = (-b + sqrt((b * b) - 4 * a * c)) / (2 * a);
	// p = startingPoint + (line direction) * (scale value)
	vec2f point1 = realStart + (realEnd - realStart) * u1;

	// Calculate where the second point of intersection is
	float u2 = (-b - sqrt((b * b) - 4 * a * c)) / (2 * a);
	vec2f point2 = realStart + (realEnd - realStart) * u2;

	printf("P1: (%.2f,%.2f)\n", point1.x, point1.y);
	printf("P2: (%.2f,%.2f)\n", point2.x, point2.y);

	bool point1OnLine = CheckPointOnEdge(point1);
	bool point2OnLine = CheckPointOnEdge(point2);

	vec2f singleCollisionPoint;
	CollisionResult* result = new CollisionResult();

	// Neither point is on the line
	if (!point1OnLine && !point2OnLine) {
		delete result;
		return nullptr;
	}
	// Both points are on the line
	else if (point1OnLine && point2OnLine) {
		vec2f chordDif = point2 - point1;
		float chordLength = chordDif.length();

		float halfChord = chordLength / 2;
		float cosChord = (halfChord / circRadius);

		float sinVal = M_PI - (M_PI_2 + cosChord);

		float chordPerpLength = sin(sinVal) * circRadius;
		float missingChordLength = circRadius - chordPerpLength; // chordPerpLength + missingChordLength = circRadius
		printf("%f\n", cosChord);

		vec2f circlePoint = vec2f((point1.x + point2.x) / 2, (point1.y + point2.y) / 2);
		printf("%f, %f", circlePoint.x, circlePoint.y);

		vec2f finalPointDir = (circPos - circlePoint).normalize();

		singleCollisionPoint = circPos + (finalPointDir * circRadius);
		result->DepenetrationDistance = missingChordLength;
	}/*
	// Only point 1 is on the line
	else if (point1OnLine) {
		singleCollisionPoint = point1;
		result->DepenetrationDistance = circRadius - (singleCollisionPoint - circPos).length();
	}
	// Only point 2 is on the line
	else {
		singleCollisionPoint = point2;
		result->DepenetrationDistance = circRadius - (singleCollisionPoint - circPos).length();
	}

	result->Obj1 = this;
	result->Obj2 = circle;
	result->Point = singleCollisionPoint;
	result->Friction = result->MixFriction(_friction, circle->GetFriction());
	result->Restitution = result->MixRestitution(_restitution, circle->GetRestitution());

	vec2f circleCenterToColPoint = circPos - singleCollisionPoint;
	result->Normal = circleCenterToColPoint.normalize();
	result->Tangent = result->Normal.perpendicular();

	return result;
}*/

bool EdgeActor::CheckPointOnEdge(vec2f point) {
	vec2f realStart = _startPoint + _position;
	vec2f realEnd = _endPoint + _position;

	if (point.x >= std::fmin(realStart.x, realEnd.x) && point.x <= std::fmax(realStart.x, realEnd.x))
	{
		if (point.y >= std::fmin(realStart.y, realEnd.y) && point.y <= std::fmax(realStart.y, realEnd.y))
			return true;
	}

	return false;
}

CollisionResult* EdgeActor::CheckCollide_Edge(EdgeActor* edge) {
	vec2f realStart = _startPoint + _position;
	vec2f realEnd = _endPoint + _position;
	vec2f otherStart = edge->GetStartPoint() + edge->GetPosition();
	vec2f otherEnd = edge->GetEndPoint() + edge->GetPosition();

	float denominator = (((otherEnd.y - otherStart.y) * (realEnd.x - realStart.x)) -
		                 ((otherEnd.x - otherEnd.x) * (realEnd.y - realStart.y)));

	if (denominator == FLT_EPSILON)
		return nullptr;

	float ua = (((otherEnd.x - otherStart.x) * (realStart.y - otherStart.y)) - 
		        ((otherEnd.y - otherStart.y) * (realStart.x - otherStart.x))) / denominator;

	float ub = (((realEnd.x - realStart.x) * (realStart.y - otherStart.y)) -
		        ((realEnd.y - realStart.y) * (realStart.x - otherStart.x))) / denominator;

	if (ua < 0 || ua > 1 || ub < 0 || ub > 1)
		return nullptr;

	return nullptr;
}

/*
// Old implementation. Doesn't work but I'll keep it here for a while
bool EdgeActor::CheckCollide_Edge(EdgeActor* edge) {
	vec2f realStart = _startPoint + _position;
	vec2f realEnd = _endPoint + _position;
	vec2f otherStart = edge->GetStartPoint() + edge->GetPosition();
	vec2f otherEnd = edge->GetEndPoint() + edge->GetPosition();

	vec2f r = realEnd - realStart;
	vec2f s = otherEnd - otherStart;

	float rCrossS = vec2f::cross(r, s);
	float qpCrossR = vec2f::cross(realStart - otherStart, r);

	// Line segments are parallel and do not intersect.
	if (rCrossS == FLT_EPSILON && qpCrossR != FLT_EPSILON)
		return false;

	float u = vec2f::cross(realStart - otherStart, r) / vec2f::cross(r, s);
	float t = vec2f::cross(realStart - otherStart, s) / vec2f::cross(r, s);

	// Line segments meet at _startPoint + direction * t
	if (rCrossS != FLT_EPSILON && (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
		return true;

	if (rCrossS == FLT_EPSILON && qpCrossR == FLT_EPSILON)
	{
		float t0 = vec2f::dot(realStart - otherStart, r) / vec2f::dot(r, r);
		float t1 = t0 + vec2f::dot(s, r) / vec2f::dot(r, r);

		printf("%f\n", t0);

		if (vec2f::dot(s, r) < 0)
		{
			if (t1 - t0 < 1)
				return true;
		}
		else
		{
			if (t1 - t0 > 0)
				return true;
		}
	}

	return false;
}*/

CollisionResult* EdgeActor::CheckCollide_BoundingBox(BoundingBox* bounds) {
	return nullptr;
}