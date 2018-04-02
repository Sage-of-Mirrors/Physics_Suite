#include "..\include\PhysicsActor.h"

void PhysicsActor::Update(float dt) {
	_momentum += _force * dt;
	_velocity = _momentum / mass;                                            
	_position += _velocity * dt;
}