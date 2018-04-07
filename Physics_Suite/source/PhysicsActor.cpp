#include "..\include\PhysicsActor.h"
const float DRAG = 10;
void PhysicsActor::Update() {
	_position += _velocity * FRAMEINTERVAL;

	/*vec2f drag(0, 0);
	if (_velocity.x > 0)
		drag.x = -DRAG;
	if (_velocity.y > 0)
		drag.y = -DRAG;
	if (_velocity.y < 0)
		drag.y = DRAG;

	ApplyForce(drag);*/

	_angle += _angular_velocity * FRAMEINTERVAL;
}

void PhysicsActor::ApplyForce(vec2f force) {
	_velocity += (force * FRAMEINTERVAL) / _mass;
}

void PhysicsActor::ApplyAcceleration(vec2f acceleration) {
	_velocity += (acceleration * FRAMEINTERVAL);
}

void PhysicsActor::ApplyImpulse(vec2f impulse) {
	_velocity += impulse / _mass;
}

void PhysicsActor::ApplyVelocity(vec2f velocity_change) {
	_velocity += velocity_change;
}

void PhysicsActor::ApplyAngularVelocity(float angular_velocity_change) {
	_angular_velocity += angular_velocity_change;
}

void PhysicsActor::ApplyPosition(vec2f position_change) {
	_position += position_change;
}

CollisionResult* PhysicsActor::CheckCollide(PhysicsActor* actor) {
	if (actor == nullptr) {
		printf("PhysicsActor pointer was null!\n");
		return nullptr;
	}

	switch (actor->GetType()) {
	case PhysicsType::CIRCLE:
		return CheckCollide_Circle((CircleActor*)actor);
	case PhysicsType::EDGE:
		return CheckCollide_Edge((EdgeActor*)actor);
	case PhysicsType::BOUNDING_BOX:
		return CheckCollide_BoundingBox((BoundingBox*)actor);
	case PhysicsType::NONE:
		return nullptr;
	default:
		assert(false); // If this happens something's fucky
	}
}