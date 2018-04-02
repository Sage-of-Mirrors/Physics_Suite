#pragma once
#include "State.h"

class BumperState : public GameState {
private:
	void RenderTopScreen();
	void RenderBottomScreen();
public:
	BumperState();
	~BumperState();
	void Enter(const StateMachine* machine);
	int Update(StateMachine* machine);
	void Render();
	void Exit();
};