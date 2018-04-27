#pragma once
#include "State.h"
#include "PhysicsActor.h"
#include "array.h"

class BumperState : public GameState {
private:
	CArrayT<PhysicsActor*> _actorColliders;
	
	void RenderTopScreen();
	void RenderBottomScreen();
public:
	BumperState();
	~BumperState() { }
	void Enter(const StateMachine* machine) { }
	int Update(StateMachine* machine);
	void Render();
	void Exit() { }
};