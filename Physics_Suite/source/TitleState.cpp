#include "..\include\TitleState.h"
#include "..\include\EdgeActor.h"
#include "..\include\Collider.h"
#include <sf2d.h>
#include <Stdio.h>

TitleState::TitleState() {
	_testCircle1 = new CircleActor(vec2f(200, 120), 100, 100, 0xff, 0xff, 0);
	_testCircle2 = new CircleActor(vec2f(50, 50), 100, 10, 0xff, 0, 0);
	_testEdge1 = new EdgeActor(vec2f(0, -50), vec2f(0, 290), 500000, 1, 1, 0xFF, 0);
	_testEdge2 = new EdgeActor(vec2f(400, -50), vec2f(400, 290), 500000, 1, 1, 0, 0xFF);
	_testEdge3 = new EdgeActor(vec2f(-50, 0), vec2f(450, 0), 500000, 1, 1, 0xFF, 0);
	_testEdge4 = new EdgeActor(vec2f(-50, 240), vec2f(450, 240), 500000, 1, 1, 0, 0xFF);

	vec2f vel = vec2f(200, 100);
	_testCircle2->ApplyVelocity(vel);
	//_testEdge2->ApplyVelocity(vel);
}

TitleState::~TitleState() {
	delete _testCircle1;
	delete _testCircle2;
	delete _testEdge1;
	delete _testEdge2;
	delete _testEdge3;
	delete _testEdge4;
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
	_testEdge3->Update();
	_testEdge4->Update();

	//_testCircle2->ApplyForce(vec2f(0, 20));

	if (hidKeysDown() & KEY_A)
		_testCircle2->ApplyImpulse(vec2f(0, -10));
	
	CollisionResult* testResult1 = _testCircle2->CheckCollide_Edge(_testEdge1);
	if (testResult1 != nullptr)
	{
		printf("Collision\n");
		Collider::ProcessCollision(testResult1);
		delete testResult1;
	}
	CollisionResult* testResult2 = _testCircle2->CheckCollide_Edge(_testEdge2);
	if (testResult2 != nullptr)
	{
		printf("Collision\n");
		Collider::ProcessCollision(testResult2);
		delete testResult2;
	}
	CollisionResult* testResult3 = _testCircle2->CheckCollide_Edge(_testEdge3);
	if (testResult3 != nullptr)
	{
		printf("Collision\n");
		Collider::ProcessCollision(testResult3);
		delete testResult3;
	}
	CollisionResult* testResult4 = _testCircle2->CheckCollide_Edge(_testEdge4);
	if (testResult4 != nullptr)
	{
		printf("Collision\n");
		Collider::ProcessCollision(testResult4);
		delete testResult4;
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
	_testEdge3->Render();
	_testEdge4->Render();

	sf2d_end_frame();
}

void TitleState::RenderBottomScreen() {
	/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);



	sf2d_end_frame();*/
}