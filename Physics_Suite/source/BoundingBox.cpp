#include "..\include\BoundingBox.h"

bool BoundingBox::CheckCollide_Circle(CircleActor* circle) {

}

bool BoundingBox::CheckCollide_Edge(EdgeActor* edge) {

}

bool BoundingBox::CheckCollide_BoundingBox(BoundingBox* bounds) {

}

void BoundingBox::Render() {
	sf2d_draw_rectangle(_position.x, _position.y, _size.x, _size.y, RGBA8(0, 0, 0, 0));
}