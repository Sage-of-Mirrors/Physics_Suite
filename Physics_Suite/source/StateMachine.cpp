#include "..\include\StateMachine.h"
#include "..\include\State.h"

void StateMachine::ChangeState(GameState* nextState) {
	if (_CurrentState)
		_CurrentState->Exit();

	_CurrentState = nextState;
	_CurrentState->Enter(this);
}

GameState* StateMachine::GetCurrentState() {
	return _CurrentState;
}

int StateMachine::Update() {
	return _CurrentState->Update(this);
}

void StateMachine::Render() {
	_CurrentState->Render();
}