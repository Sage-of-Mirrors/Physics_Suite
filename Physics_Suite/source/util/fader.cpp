#include "..\..\include\util\fader.h"
#include <Stdio.h>

Fader::Fader(bool fadingIn) {
	fadeIn = fadingIn;

	if (fadeIn) {
		color = 0xFF000000;
	}
}

void Fader::SetColor(char r, char g, char b, char a) {
	color = RGBA8(r, g, b, a);
}

int Fader::Update() {
	int alpha = (color & 0xFF000000) >> 24; // We need the current alpha value as an integer

	printf("%d\n", alpha);

	if (fadeIn) {
		alpha -= speed;

		if (alpha <= 0) {
			return 1;
		}
	}

	else {
		alpha += speed;

		if (alpha >= 255) {
			return 1;
		}
	}

	color = color & 0x00FFFFFF; // Zero the original alpha value
	color |= (alpha << 24) & 0xFF000000; // Insert the modified value

	return 0;
}

void Fader::Render() {
	sf2d_draw_rectangle(0, 0, width, height, color);
}