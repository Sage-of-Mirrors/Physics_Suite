#include "..\include\PhysicsActor.h"

void PhysicsActor::Update(float dt) {                                           
	_position += _velocity * dt;
}

void PhysicsActor::ApplyForce(vec2f force, float dt) {
	_velocity += (force * dt) / _mass;
}

void PhysicsActor::ApplyAcceleration(vec2f acceleration, dt) {
	_velocity += (acceleration * dt);
}

void PhysicsActor::ApplyImpulse(vec2f impulse) {
	_velocity += impulse / _mass;
}

void PhysicsActor::ApplyVelocity(vec2f velocity_change) {
	_velocity += velocity_change;
}