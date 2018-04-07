#include "..\include\Collider.h"

void Collider::ProcessCollision(CollisionResult* result) {
	if (result == nullptr)
		return;
	
	Depenetration(result);
	Repulsion(result);
}

void Collider::Depenetration(CollisionResult* result) {
	float mass_mu = Calc_Mu(result->Obj1, result->Obj2);
	vec2f depenetrationVec = result->Normal * result->DepenetrationDistance;

	result->Obj1->ApplyPosition(depenetrationVec * (mass_mu / result->Obj1->GetMass()));
	result->Obj2->ApplyPosition(-(depenetrationVec * (mass_mu / result->Obj2->GetMass())));

	vec2f velocityDif = result->Obj1->GetVelocity() - result->Obj2->GetVelocity();
	vec2f positionDif = result->Obj1->GetPosition() - result->Obj2->GetPosition();
	float L = mass_mu * vec2f::cross(positionDif, velocityDif);

	//vec2f j_Perpendicular = positionDif.normalize().perpendicular() * ((-result->DepenetrationDistance) / (positionDif.length() * (positionDif.length() + result->DepenetrationDistance))) * L;
	vec2f j_Perpendicular = positionDif.normalize().perpendicular()  * ((-result->DepenetrationDistance) / (positionDif.length() * (positionDif.length() + result->DepenetrationDistance))) * L;

	result->Obj1->ApplyForce(j_Perpendicular);
	result->Obj2->ApplyForce(-j_Perpendicular);
}

void Collider::Repulsion(CollisionResult* result) {
	float mass_mu = Calc_Mu(result->Obj1, result->Obj2);
	vec2f velocityDif = result->Obj1->GetVelocity() - result->Obj2->GetVelocity();
	
	vec2f j = velocityDif * -(1 + 0.5) * mass_mu;

	if (vec2f::dot(velocityDif, result->Normal) < 0)
		j = result->Normal * vec2f::dot(j, result->Normal);
	else
		j = vec2f(0, 0);

	result->Obj1->ApplyImpulse(j);
	result->Obj2->ApplyImpulse(-j);
	
	// Apply repulsion
	/*float j = vec2f::dot(velocityDif, result->Normal) * -(1 + 0result->Restitution) * mass_mu;
	
	// Apply friction
	vec2f jFriction = result->Tangent * vec2f::dot(velocityDif, result->Tangent) * -mass_mu;
	
	float f = result->Friction * j;
	
	if (jFriction.length() > f)
		jFriction *= f / jFriction.length();
	
	vec2f J_final = (result->Normal * j); //+ (result->Tangent * jFri)
	
	result->Obj1->ApplyImpulse(J_final);
	result->Obj2->ApplyImpulse(-J_final);*/
}

float Collider::Calc_Mu(PhysicsActor* first, PhysicsActor* second) {
	return 1 / ((1 / first->GetMass()) + (1 / second->GetMass()));
}