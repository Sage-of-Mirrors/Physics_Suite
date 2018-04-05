#include "..\include\EdgeActor.h"
#include "..\include\CircleActor.h"

void EdgeActor::Render() {
	sf2d_draw_line(_startPoint.x, _startPoint.y,
		_endPoint.x, _endPoint.y,
		_width, RGBA8(_r, _g, _b, 0xFF));
}

bool EdgeActor::CheckCollide_Circle(CircleActor* circle) {
	// First, we calculate a, b, and c for the equation that describes the intersection between a line and a circle:
	// a^2 * u + b * u + c
	float a = (_endPoint.x - _startPoint.x) * (_endPoint.x - _startPoint.x) +
			  (_endPoint.y - _startPoint.y) * (_endPoint.y - _startPoint.y);

	float b = 2 * 
		      (_startPoint.x * (_endPoint.x - _startPoint.x) +
			   _startPoint.y * (_endPoint.y - _startPoint.y));

	float c = (_startPoint.x * _startPoint.x) + (_startPoint.y * _startPoint.y) - (circle->GetRadius() * circle->GetRadius());

	float delta = (b * b) - 4 * a * c;

	// There are no solutions to the intersection equation, so there is no intersection.
	if (delta < 0)
		return false;

	// Calculate where the first point of intersection is
	float u1 = (-b + sqrt((b * b) - 4 * a * c)) / (2 * a);
	// p = startingPoint + (line direction) * (scale value)
	vec2f point1 = _startPoint + (_endPoint - _startPoint) * u1;

	// Point was on the line segment. This is a valid collision.
	if (CheckPointOnEdge(point1))
		return true;
	// delta == 0 means there is only one point of intersection. The point we calculated above was not on the line segment,
	// so the collision is not valid.
	else if (delta == 0)
		return false;

	// Calculate where the second point of intersection is
	float u2 = (-b - sqrt((b * b) - 4 * a * c)) / (2 * a);
	vec2f point2 = _startPoint + (_endPoint - _startPoint) * u2;

	return CheckPointOnEdge(point2);
}

bool EdgeActor::CheckPointOnEdge(vec2f point) {
	float cross = vec2<float>::cross(_endPoint - point, _startPoint - point);
	if (abs(cross) > FLT_EPSILON)
		return false;

	float dot = vec2<float>::dot(_endPoint - point, _startPoint - point);
	if (dot < 0)
		return false;

	float squareLength = (_endPoint - _startPoint).length();
	if (dot > squareLength)
		return false;

	return true;
}

bool EdgeActor::CheckCollide_Edge(EdgeActor* edge) {
	vec2f r = _endPoint - _startPoint;
	vec2f s = edge->GetEndPoint() - edge->GetStartPoint();

	float rCrossS = vec2f::cross(r, s);
	float qpCrossR = vec2f::cross(_startPoint - edge->GetStartPoint(), r);

	// Line segments are parallel and do not intersect.
	if (rCrossS == FLT_EPSILON && qpCrossR != FLT_EPSILON)
		return false;

	float u = vec2f::cross(_startPoint - edge->GetStartPoint(), r) / vec2f::cross(r, s);
	float t = vec2f::cross(_startPoint - edge->GetStartPoint(), s) / vec2f::cross(r, s);

	// Line segments meet at _startPoint + direction * t
	if (rCrossS != FLT_EPSILON && (t >= 0) && (t <= 1) && (u >= 0) && (u <= 1))
		return true;

	if (rCrossS == FLT_EPSILON && qpCrossR == FLT_EPSILON)
	{
		float t0 = vec2f::dot(_startPoint - edge->GetStartPoint(), r) / vec2f::dot(r, r);
		float t1 = t0 + vec2f::dot(s, r) / vec2f::dot(r, r);

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
}

bool EdgeActor::CheckCollide_BoundingBox(BoundingBox* bounds) {
	return false;
}