#include "..\include\TitleState.h"
#include <sf2d.h>
#include <Stdio.h>

TitleState::TitleState() {
	_testCircle1 = new CircleActor(vec2f(200, 120), 1, 50, 0xff, 0xff, 0);
	_testCircle2 = new CircleActor(vec2f(0, 120), 1, 20, 0xff, 0, 0);
}

TitleState::~TitleState() {
	delete _testCircle1;
	delete _testCircle2;
}

void TitleState::Enter(const StateMachine* machine) {

}

void TitleState::Exit() {

}

int TitleState::Update(StateMachine* machine) {
	if (hidKeysDown() & KEY_START)
		return 1;

	_testCircle1->Update();
	_testCircle2->Update();

	return 0;
}

void TitleState::Render() {
	RenderTopScreen();
	RenderBottomScreen();
}

void TitleState::RenderTopScreen() {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);

	_testCircle1->Render();
	_testCircle2->Render();

	sf2d_end_frame();
}

void TitleState::RenderBottomScreen() {
	/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);



	sf2d_end_frame();*/
}