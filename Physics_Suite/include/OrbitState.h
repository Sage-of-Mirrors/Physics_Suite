#pragma once
#include "State.h"

class OrbitState : public GameState {
private:
	void RenderTopScreen();
	void RenderBottomScreen();
public:
	OrbitState();
	~OrbitState();
	void Enter(const StateMachine* machine);
	int Update(StateMachine* machine);
	void Render();
	void Exit();
};