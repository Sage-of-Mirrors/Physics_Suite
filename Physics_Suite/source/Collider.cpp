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
	
	// Calculate repulsion
	float jN = vec2f::dot(velocityDif, result->Normal) * -(1 + result->Restitution) * mass_mu;

	if (jN > 0)
		return;

	// Calculate friction
	float jT = -vec2f::dot(velocityDif, newTangent) * mass_mu;

	if (math::abs(jT) > result->Friction * math::abs(jN))
		jf *= (result->Friction * math::abs(jN)) / math::abs(jT);
	
	// Apply forces
	vec2f j_Final = (result->Normal * jN) + (result->Tangent * jT);

	if (!result->Obj1->GetIsStatic())
		result->Obj1->ApplyImpulse(-j_Final);
	if (!result->Obj2->GetIsStatic())
		result->Obj2->ApplyImpulse(j_Final);
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