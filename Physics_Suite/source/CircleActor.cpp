#include "..\include\CircleActor.h"
#include "..\include\EdgeActor.h"

CircleActor::CircleActor(vec2f pos, float mass, float rad, char r, char g, char b) {
	_type = PhysicsType::CIRCLE;
	_position = pos;
	_mass = mass;
	_radius = rad;
	_r = r;
	_g = g;
	_b = b;

	_velocity = vec2f(0, 0);
}

void CircleActor::Render() {
	sf2d_draw_fill_circle(_position.x, _position.y, _radius, RGBA8(_r, _g, _b, 0xFF));
}

CollisionResult* CircleActor::CheckCollide_Circle(CircleActor* circle) {
	vec2f distVec = circle->GetPosition() - _position;
	float radii = circle->GetRadius() + _radius;

	// Collision occurs if the distance between the two circles is less than the sum of their radii
	if (distVec.length() < radii)
	{
		CollisionResult* result = new CollisionResult();
		
		vec2f distNormal = distVec.normalize();
		vec2f contactPoint = _position + (distVec.length() * distNormal);
		result->Points = CArrayT<vec2f> { contactPoint };
		
		vec2f centerToContact = contactPoint - _position;
		result->Normal = centerToContact.perpendicular();
		return result;
	}
	else
		return nullptr;
}

CollisionResult* CircleActor::CheckCollide_Edge(EdgeActor* edge) {
	return edge->CheckCollide_Circle(this);
}

CollisionResult* CircleActor::CheckCollide_BoundingBox(BoundingBox* bounds) {
	return bounds->CheckCollide_Circle(this);
}