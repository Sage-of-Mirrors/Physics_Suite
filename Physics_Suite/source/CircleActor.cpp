#include "..\include\CircleActor.h"

CircleActor::CircleActor(vec2f* pos, float mass, float rad, char r, char g, char b) {
	_position = pos;
	_mass = mass;
	_radius = rad;
	_r = r;
	_g = g;
	_b = b;

	_velocity = new vec2f(0, 0);
}

void CircleActor::Render() {
	sf2d_draw_fill_circle(_position->x, _position->y, _radius, RGBA8(_r, _g, _b, 0xFF));
}