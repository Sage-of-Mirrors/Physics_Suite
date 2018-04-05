#include "..\include\EdgeActor.h"
#include "..\include\CircleActor.h"

EdgeActor::EdgeActor(vec2f startPos, vec2f endPos, float width, char r, char g, char b) {
	_startPoint = startPos;
	_endPoint = endPos;
	_width = width;
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
	// First, we calculate a, b, and c for the equation that describes the intersection between a line and a circle:
	// a^2 * u + b * u + c
	vec2f circPos = circle->GetPosition();
	float circRadius = circle->GetRadius();

	float dx = _endPoint.x - _startPoint.x;
	float dy = _endPoint.y - _startPoint.y;

	float a = (dx) * (dx) +
			  (dy) * (dy);

	float b = 2 * 
		      (dx * (_startPoint.x - circPos.x) +
			   dy * (_startPoint.y - circPos.y));

	float c = ((_startPoint.x - circPos.x) * (_startPoint.x - circPos.x)) +
		      ((_startPoint.y - circPos.y) * (_startPoint.y - circPos.y)) - 
		      (circRadius * circRadius);

	float delta = (b * b) - 4 * a * c;

	// There are no solutions to the intersection equation, so there is no intersection.
	if (a <= FLT_EPSILON || delta < FLT_EPSILON)
		return nullptr;
	
	CollisionResult* result = new CollisionResult();

	// Calculate where the first point of intersection is
	float u1 = (-b + sqrt((b * b) - 4 * a * c)) / (2 * a);
	// p = startingPoint + (line direction) * (scale value)
	vec2f point1 = _startPoint + (_endPoint - _startPoint) * u1;

	// Point was on the line segment. This is a valid collision.
	if (CheckPointOnEdge(point1))
		result->Points.push_back(point1);
	// delta == 0 means there is only one point of intersection. The point we calculated above was not on the line segment,
	// so the collision is not valid.
	else if (delta == 0)
	{
		delete result;
		return nullptr;
	}

	// Calculate where the second point of intersection is
	float u2 = (-b - sqrt((b * b) - 4 * a * c)) / (2 * a);
	vec2f point2 = _startPoint + (_endPoint - _startPoint) * u2;

	if (CheckPointOnEdge(point2))
		result->Points.push_back(point2);
	
	if (result->Points.size() > 0)
	{
		vec2f startToIntersection = point1 - _startPoint;
		result->Normal = startToIntersection.perpendicular;
		
		return result;
	}
	else
	{
		delete result;
		return nullptr;
	}
}

bool EdgeActor::CheckPointOnEdge(vec2f point) {
	/*
	float cross = vec2<float>::cross(_endPoint - point, _startPoint - point);
	if (abs(cross) > FLT_EPSILON)
		return false;

	float dot = vec2<float>::dot(_endPoint - point, _startPoint - point);
	if (dot < 0)
		return false;

	float squareLength = (_endPoint - _startPoint).length();
	if (dot > squareLength)
		return false;

	printf("true\n");
	return true;*/

	if (point.x >= std::fmin(_startPoint.x, _endPoint.x) && point.x <= std::fmax(_startPoint.x, _endPoint.x))
	{
		if (point.y >= std::fmin(_startPoint.y, _endPoint.y) && point.y <= std::fmax(_startPoint.y, _endPoint.y))
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
		return false;

	float ua = (((otherEnd.x - otherStart.x) * (realStart.y - otherStart.y)) - 
		        ((otherEnd.y - otherStart.y) * (realStart.x - otherStart.x))) / denominator;

	float ub = (((realEnd.x - realStart.x) * (realStart.y - otherStart.y)) -
		        ((realEnd.y - realStart.y) * (realStart.x - otherStart.x))) / denominator;

	if (ua < 0 || ua > 1 || ub < 0 || ub > 1)
		return false;

	return true;
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

bool EdgeActor::CheckCollide_BoundingBox(BoundingBox* bounds) {
	return false;
}