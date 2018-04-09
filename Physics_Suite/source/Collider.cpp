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

	if (!result->Obj1->GetIsStatic())
		result->Obj1->ApplyPosition(depenetrationVec * (mass_mu / result->Obj1->GetMass()));
	if (!result->Obj2->GetIsStatic())
		result->Obj2->ApplyPosition(-(depenetrationVec * (mass_mu / result->Obj2->GetMass())));
}

void Collider::Repulsion(CollisionResult* result) {
	float mass_mu = Calc_Mu(result->Obj1, result->Obj2);

	vec2f velocityDif = Calc_VelocityDifference(result->Obj1, result->Obj2);
	
	// Apply repulsion
	float jN = vec2f::dot(velocityDif, result->Normal) * -(1 + result->Restitution) * mass_mu;

	if (jN > 0)
		return;

	printf("jN: %f\n", jN);

	if (!result->Obj1->GetIsStatic())
		result->Obj1->ApplyImpulse(-result->Normal * jN);
	if (!result->Obj2->GetIsStatic())
		result->Obj2->ApplyImpulse(result->Normal * jN);

	velocityDif = Calc_VelocityDifference(result->Obj1, result->Obj2);
	vec2f newTangent = velocityDif - (result->Normal * vec2f::dot(velocityDif, result->Normal));
	newTangent = newTangent.normalize();

	// Apply friction
	vec2f jf = newTangent * -mass_mu * vec2f::dot(velocityDif, newTangent);

	if (jf.length() > (result->Normal * result->Friction * jN).length())
		jf *= (result->Normal * result->Friction * jN).length() / jf.length();

	if (!result->Obj1->GetIsStatic())
		result->Obj1->ApplyImpulse(-jf);
	if (!result->Obj2->GetIsStatic())
		result->Obj2->ApplyImpulse(jf);
}

float Collider::Calc_Mu(PhysicsActor* first, PhysicsActor* second) {
	float denom = 0;

	if (!first->GetIsStatic())
		denom += (1 / first->GetMass());
	if (!second->GetIsStatic())
		denom += (1 / second->GetMass());

	return 1 / denom;
}

vec2f Collider::Calc_VelocityDifference(PhysicsActor* first, PhysicsActor* second) {
	if (!first->GetIsStatic() && second->GetIsStatic())
		return first->GetVelocity();
	
	if (first->GetIsStatic() && !second->GetIsStatic())
		return second->GetVelocity();
	
	else
		return second->GetVelocity() - first->GetVelocity();
}