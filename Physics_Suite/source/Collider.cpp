#include "..\include\Collider.h"

static void Collider::ProcessCollision(CollisionResult* result) {
	if (result == nullptr)
		return;
	
	Depenetration(result);
	Repulsion(result);
}

static void Collider::Depenetration(CollisionResult* result) {
	float mass_mu = Calc_Mu(result->Obj1, result->Obj2);
	vec2f depenetrationVec = result->DepenetrationDistance * result->Direction;
	
	result->Obj1->ApplyPosition((mass_mu / result->Obj1->GetMass()) * depenetrationVec);
	result->Obj2->ApplyPosition((mass_mu / result->Obj2->GetMass()) * depenetrationVec);
}

static void Collider::Repulsion(CollisionResult* result) {
	float mass_mu = Calc_Mu(result->Obj1, result->Obj2);
	vec2f velocityDif = result->Obj2->GetVelocity() - result->Obj1->GetVelocity();
	
	// Apply repulsion
	vec2f j = (1 + result->Restitution) * mass_mu * velocityDif;
	
	if (vec2f::dot(vel_dif, result->Direction) < 0)
		j = vec2f::dot(j, result->Direction) * result->Direction;
	else
		j = 0;
	
	// Apply friction
	vec2f jFriction = -mu * vec2f::dot(velocityDif, result->Direction) * result->Direction();
	
	if (jFriction.length() > (result->Friction * j).length())
		jFriction *= (result->Friction * j).length() / jFriction.length();
	
	J -= jFriction;
	
	result->Obj1->ApplyImpulse(j);
	result->Obj2->ApplyImpulse(-j);
}

static float Collider::Calc_Mu(PhysicsActor* first, PhysicsActor* second) {
	return 1 / ((1 / first->GetMass()) + (1 / second->GetMass()));
}