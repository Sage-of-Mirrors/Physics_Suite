#include "..\include\CircleActor.h"
#include "..\include\EdgeActor.h"
#include "..\include\BoundingBox.h"

CircleActor::CircleActor(vec2f position, float radius, float mass, float friction, float restitution, int color, bool isStatic) {
	_type = PhysicsType::CIRCLE;

	_position = position;
	_radius = radius;
	_mass = mass;
	_friction = friction;
	_restitution = restitution;
	_color = color;
	_static = isStatic;

	_velocity = vec2f(0, 0);
}

void CircleActor::Render() {
	sf2d_draw_fill_circle(_position.x, _position.y, _radius, _color);
}

CollisionResult* CircleActor::CheckCollide_Circle(CircleActor* circle) {
	vec2f distVec = _position - circle->GetPosition();
	float radii = circle->GetRadius() + _radius;

	// Collision occurs if the distance between the two circles is less than the sum of their radii
	if (distVec.length() < radii)
	{
		CollisionResult* result = new CollisionResult();
		result->Obj1 = this;
		result->Obj2 = circle;
		result->DepenetrationDistance = radii - distVec.length();
		
		vec2f distNormal = distVec.normalize();
		vec2f contactPoint = _position + (distNormal * distVec.length());
		result->Point = contactPoint;
		
		result->Normal = distNormal;
		result->Tangent = result->Normal.perpendicular();
		
		result->Friction = result->MixFriction(_friction, circle->GetFriction());
		result->Restitution = result->MixRestitution(_restitution, circle->GetRestitution());
		
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

bool CircleActor::CheckPointInCircle(vec2f point) {
	if ((point - _position).length() <= _radius)
		return true;
	else
		return false;
}