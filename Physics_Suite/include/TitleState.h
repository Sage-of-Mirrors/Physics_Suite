#pragma once
#include "State.h"
#include "array.h"

class TitleState : public GameState {
private:
	void RenderTopScreen();
	void RenderBottomScreen();
	int x = 0;
	int x_sp = 5;
	CArrayT<int> _testArray;
public:
	TitleState();
	~TitleState();
	void Enter(const StateMachine*);
	int Update(StateMachine*);
	void Render();
	void Exit();
};