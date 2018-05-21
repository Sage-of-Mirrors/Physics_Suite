#pragma once
#include <sf2d.h>

class Fader {
private:
	const int width = 400;
	const int height = 240;
	const int speed = 10;
	int32_t color;
	bool fadeIn;
public:
	Fader(bool fadingIn);
	void SetColor(char r, char g, char b, char a);
	int Update();
	void Render();
};