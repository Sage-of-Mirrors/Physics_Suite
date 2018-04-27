#pragma once
#include "State.h"

class PlatformerState : public GameState {
private:
	void RenderTopScreen();
	void RenderBottomScreen();
	//std::vector<actor> _actors;
public:
	PlatformerState();
	~PlatformerState();
	void Enter(const StateMachine* machine);
	int Update(StateMachine* machine);
	void Render();
	void Exit();
};