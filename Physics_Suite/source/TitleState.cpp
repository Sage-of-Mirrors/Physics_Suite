#include "..\include\TitleState.h"
#include "..\include\EdgeActor.h"
#include <sf2d.h>
#include <Stdio.h>

TitleState::TitleState() {
	_testCircle1 = new CircleActor(vec2f(200, 120), 1, 50, 0xff, 0xff, 0);
	_testCircle2 = new CircleActor(vec2f(0, 120), 1, 20, 0xff, 0, 0);
	_testEdge1 = new EdgeActor(vec2f(0, 240), vec2f(400, 0), 1, 0, 0xFF, 0);
	_testEdge2 = new EdgeActor(vec2f(0, 120), vec2f(100, 120), 1, 0, 0, 0xFF);

	vec2f vel = vec2f(50, 0);
	//_testCircle2->ApplyVelocity(vel);
	_testEdge2->ApplyVelocity(vel);
}

TitleState::~TitleState() {
	delete _testCircle1;
	delete _testCircle2;
	delete _testEdge1;
	delete _testEdge2;
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
	_testEdge1->Update();
	_testEdge2->Update();

	if (_testEdge2->CheckCollide_Edge(_testEdge1))
	{
		_testEdge2->SetColor(255, 255, 255);
		printf("collided\n");
	}
	else
	{
		_testEdge2->SetColor(0, 0, 255);
		printf("no collision\n");
	}

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
	_testEdge1->Render();
	_testEdge2->Render();

	sf2d_end_frame();
}

void TitleState::RenderBottomScreen() {
	/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);



	sf2d_end_frame();*/
}