#include "..\include\PhysicsActor.h"

void PhysicsActor::Update() {
	_position += _velocity * FRAMEINTERVAL;

	/*vec2f drag(0, 0);
	if (_velocity->x > 0)
		drag.x = -DRAG;
	if (_velocity->y > 0)
		drag.y = -DRAG;
	if (_velocity->y < 0)
		drag.y = DRAG;

	ApplyForce(drag);*/

	_angle += _angular_velocity * FRAMEINTERVAL;
}

void PhysicsActor::ApplyForce(vec2f& force) {
	_velocity += (force * FRAMEINTERVAL) / _mass;
}

void PhysicsActor::ApplyAcceleration(vec2f& acceleration) {
	_velocity += (acceleration * FRAMEINTERVAL);
}

void PhysicsActor::ApplyImpulse(vec2f& impulse) {
	_velocity += impulse / _mass;
}

void PhysicsActor::ApplyVelocity(vec2f& velocity_change) {
	_velocity += velocity_change;
}

void PhysicsActor::ApplyAngularVelocity(float angular_velocity_change) {
	_angular_velocity += angular_velocity_change;
}