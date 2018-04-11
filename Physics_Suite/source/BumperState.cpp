#include "..\include\BumperState.h"

const int COL_ITERATIONS = 5;

BumperState::BumperState() {
	
}

int BumperState::Update(StateMachine* machine) { 
	for (int i = 0; i < COL_ITERATIONS; i++) {
		for (int i = 0; i < _actorColliders.size(); i++) {
		_actorColliders[i]->Update();
		}
		
		for (int b = 0; b < _actorColliders.size(); b++) {
			PhysicsActor* curActor = _actorColliders[i];
			
			for (int j = b + 1; j < _actorColliders.size(); b++) {
				curActor->CheckCollide(_actorColliders[j]);
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
	sf2d_draw_rectangle(0,0,405,245, RGBA8(255, 255, 255, 255));
	
	// Objects
	for (int i = 0; i < _actorColliders.size(); i++) {
		_actorColliders[i]->Render();
	}

	sf2d_end_frame();
}

void BumperState::RenderBottomScreen() {
	sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);

	sf2d_end_frame();
}