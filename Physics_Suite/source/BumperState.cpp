#include "..\include\BumperState.h"
#include "..\include\random.h"
#include "..\include\CircleActor.h"
#include "..\include\Collider.h"
#include "..\include\CollisionResult.h"
#include <time.h>

const int COL_ITERATIONS = 5;

BumperState::BumperState() {
	CFastRandom rand;
	rand.seed((int)time(NULL));
	
	// Generate circles. Minimum of 2, maximum of 15
	int numCircles = (rand.getUint() % (14)) + 2;
	
	for (int i = 0; i < numCircles; i++) {
		vec2f randomPosition = rand.getVector();
		int randomRadius = (rand.getUint() % (7)) + 3;
		int randomColor = rand.getUint();
		vec2f randomVelocity = rand.getVector();
		
		CircleActor* circ = new CircleActor(randomPosition, randomRadius, randomRadius * 12, 0.0f, 0.86f, randomColor, false);
		circ->ApplyVelocity(randomVelocity);
		
		_actorColliders.append((PhysicsActor*)circ);
	}
}

int BumperState::Update(StateMachine* machine) {

	/*for (int i = 0; i < COL_ITERATIONS; i++) {
		for (int i = 0; i < _actorColliders.size(); i++) {
		_actorColliders[i]->Update();
		}
		
		for (int b = 0; b < _actorColliders.size(); b++) {
			PhysicsActor* curActor = _actorColliders[i];
			
			for (int j = b + 1; j < _actorColliders.size(); b++) {
				curActor->CheckCollide(_actorColliders[j]);
			}
		}
	}*/
		
	
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
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

	// Background
	sf2d_draw_rectangle(0, 0, 405, 245, RGBA8(50, 50, 50, 255));

	sf2d_end_frame();
}