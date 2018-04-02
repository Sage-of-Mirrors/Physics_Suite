#include "..\include\PhysicsActor.h"

void PhysicsActor::Update() {                                           
	_position += _velocity * FRAMEINTERVAL;
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