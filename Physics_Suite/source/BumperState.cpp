#include "..\include\BumperState.h"
#include "..\include\random.h"
#include "..\include\CircleActor.h"
#include "..\include\EdgeActor.h"
#include "..\include\Collider.h"
#include "..\include\CollisionResult.h"
#include <time.h>

const int COL_ITERATIONS = 5;

BumperState::BumperState() {
	CFastRandom rand;
	rand.seed((int)time(NULL));

	_actorColliders.append(new EdgeActor(vec2f(0, 0),   vec2f(0, 240),   1, 0, 1, 1, true, 0, 0, 0));
	_actorColliders.append(new EdgeActor(vec2f(400, 0), vec2f(400, 240), 1, 0, 1, 2, true, 0, 0, 0));
	_actorColliders.append(new EdgeActor(vec2f(0, 0),   vec2f(400, 0),   1, 0, 1, 1, true, 0, 0, 0));
	_actorColliders.append(new EdgeActor(vec2f(0, 240), vec2f(400, 240), 1, 0, 1, 2, true, 0, 0, 0));
	
	// Generate circles. Minimum of 2, maximum of 15
	int numCircles = (rand.getUint() % (14)) + 2;
	
	for (int i = 0; i < 20; i++) {
		vec2f randomPosition = rand.getVector(20, 380, 20, 220);
		int randomRadius = (rand.getUint() % (20 - 3 + 1)) + 3;
		int randomColor = rand.getColor();
		vec2f randomVelocity = rand.getVector(10, 30, 10, 30);
		
		CircleActor* circ = new CircleActor(randomPosition, randomRadius, randomRadius * 12, 0.0f, 0.9f, randomColor, false);
		circ->ApplyVelocity(randomVelocity);
		
		_actorColliders.append((PhysicsActor*)circ);
	}
}

int BumperState::Update(StateMachine* machine) {

	for (int i = 0; i < 5; i++) {
		for (int i = 0; i < _actorColliders.size(); i++) {
		_actorColliders[i]->Update();
		}
		
		for (int b = 0; b < _actorColliders.size(); b++) {
			PhysicsActor* curActor = _actorColliders[b];
			
			for (int j = b + 1; j < _actorColliders.size(); j++) {
				CollisionResult* result = curActor->CheckCollide(_actorColliders[j]);

				if (result != nullptr)
				{
					Collider::ProcessCollision(result);
				}
			}
		}
	}
		
	
	return 0;
}

void BumperState::Render() {
	RenderTopScreen();
	RenderBottomScreen();
}

void BumperState::RenderTopScreen() {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);
	
	// Background
	sf2d_draw_rectangle(0, 0, 405, 245, RGBA8(196, 196, 196, 255));
	
	// Objects
	for (int i = 0; i < _actorColliders.size(); i++) {
		_actorColliders[i]->Render();
	}

	sf2d_end_frame();
}

void BumperState::RenderBottomScreen() {
	/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

	// Background
	sf2d_draw_rectangle(0, 0, 405, 245, RGBA8(50, 50, 50, 255));

	sf2d_end_frame();*/
}