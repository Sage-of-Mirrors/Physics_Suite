#pragma once
#include "StateMachine.h"

class GameState {
protected:
	virtual void RenderTopScreen() = 0;
	virtual void RenderBottomScreen() = 0;
public:
	virtual ~GameState() { }
	virtual void Enter(const StateMachine*) = 0;
	virtual int Update(StateMachine*) = 0;
	virtual void Render() = 0;
	virtual void Exit() = 0;
};