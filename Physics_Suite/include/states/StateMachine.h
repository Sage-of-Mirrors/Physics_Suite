#pragma once

class GameState;

class StateMachine {
private:
	GameState* _CurrentState;
public:
	void ChangeState(GameState*);
	GameState* GetCurrentState();
	int Update();
	void Render();
};