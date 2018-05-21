#pragma once
#include "State.h"
#include "..\physics\PhysicsActor.h"
#include "..\util\array.h"
#include "..\util\fader.h"

class BumperState : public GameState {
private:
	CArrayT<PhysicsActor*> _actorColliders;
	bool fading;
	Fader* fader;
	
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