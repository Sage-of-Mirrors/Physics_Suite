#include "..\include\TitleState.h"
#include <sf2d.h>
#include <Stdio.h>

TitleState::TitleState() {

}

TitleState::~TitleState() {

}

void TitleState::Enter(const StateMachine* machine) {

}

void TitleState::Exit() {

}

int TitleState::Update(StateMachine* machine) {
	if (hidKeysDown() & KEY_START)
		return 1;

	if (x > 400)
		x_sp = -x_sp;
	else if (x < 0)
		x_sp = -x_sp;

	x += x_sp;

	if (_testArray.size() < 10)
		_testArray.append(x);

	return 0;
}

void TitleState::Render() {
	RenderTopScreen();
	RenderBottomScreen();
}

void TitleState::RenderTopScreen() {
	sf2d_start_frame(GFX_TOP, GFX_LEFT);

	sf2d_draw_fill_circle(x, 120, 50, RGBA8(0xFF, 0, 0, 0xFF));

	sf2d_end_frame();
}

void TitleState::RenderBottomScreen() {
	/*sf2d_start_frame(GFX_BOTTOM, GFX_LEFT);



	sf2d_end_frame();*/

	for (int i = 0; i < _testArray.size(); i++) {
		printf("%d ", _testArray.at(i));
	}

	printf("\n");
}