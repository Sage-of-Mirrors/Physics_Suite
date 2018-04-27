#include "..\include\TitleState.h"
#include "..\include\EdgeActor.h"
#include "..\include\Collider.h"
#include "..\include\random.h"
#include <sf2d.h>
#include <Stdio.h>
#include <time.h>

TitleState::TitleState() {
	_testCircle1 = new CircleActor(vec2f(200, 120), 10, 10, .000, 1, RGBA8(0xFF, 0xFF, 0xFF, 0xFF), false);
	_testCircle2 = new CircleActor(vec2f(200, 120), 10, 10, 0.000, 1, RGBA8(0xFF, 0, 0, 0xFF), false);
	_testEdge1 = new EdgeActor(vec2f(0, 0), vec2f(0, 240), 1, 0, 1, 1, true, 0xFF, 0xFF, 0xFF);
	_testEdge2 = new EdgeActor(vec2f(400, 0), vec2f(400, 240), 1, .0, 1, 1, true, 0xFF, 0xFF, 0xFF);
	_testEdge3 = new EdgeActor(vec2f(0, 0), vec2f(400, 0), 1, .0, 1, 1, true, 0xFF, 0xFF, 0xFF);
	_testEdge4 = new EdgeActor(vec2f(0, 240), vec2f(400, 240), 1, 0, 1, 1, true, 0xFF, 0xFF, 0xFF);

	vec2f vel = vec2f(100, 0);
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
	for (int i = 0; i < 5; i++)
	{
		_testCircle1->Update();
		_testCircle2->Update();
		_testEdge1->Update();
		_testEdge2->Update();
		_testEdge3->Update();
		_testEdge4->Update();

		//printf("%f, %f\n", _testCircle2->GetVelocity().x, _testCircle2->GetVelocity().y);
		//_testCircle2->ApplyForce(vec2f(0, 900));
		//_testCircle1->ApplyForce(vec2f(0, 900));

		if (hidKeysDown() & KEY_A)
			_testCircle2->ApplyImpulse(vec2f(200, 200));

		CollisionResult* testResult1 = _testCircle1->CheckCollide_Edge(_testEdge1);
		if (testResult1 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult1);
			delete testResult1;
		}
		CollisionResult* testResult2 = _testCircle1->CheckCollide_Edge(_testEdge2);
		if (testResult2 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult2);
			delete testResult2;
		}
		CollisionResult* testResult3 = _testCircle1->CheckCollide_Edge(_testEdge3);
		if (testResult3 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult3);
			delete testResult3;
		}
		CollisionResult* testResult4 = _testCircle1->CheckCollide_Edge(_testEdge4);
		if (testResult4 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult4);
			delete testResult4;
		}

		CollisionResult* testResult5 = _testCircle2->CheckCollide_Edge(_testEdge1);
		if (testResult5 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult5);
			delete testResult5;
		}
		CollisionResult* testResult6 = _testCircle2->CheckCollide_Edge(_testEdge2);
		if (testResult6 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult6);
			delete testResult6;
		}
		CollisionResult* testResult7 = _testCircle2->CheckCollide_Edge(_testEdge3);
		if (testResult7 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult7);
			delete testResult7;
		}
		CollisionResult* testResult8 = _testCircle2->CheckCollide_Edge(_testEdge4);
		if (testResult8 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult8);
			delete testResult8;
		}

		CollisionResult* testResult9 = _testCircle1->CheckCollide_Circle(_testCircle2);
		if (testResult9 != nullptr)
		{
			printf("Collision\n");
			Collider::ProcessCollision(testResult9);
			delete testResult9;
		}
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