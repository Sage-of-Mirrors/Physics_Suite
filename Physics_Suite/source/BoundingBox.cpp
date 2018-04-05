#include "..\include\BoundingBox.h"

bool BoundingBox::CheckCollide_Circle(CircleActor* circle) {
	vec2f circPos = circle->GetPosition();
	float circRadius = circle->GetRadius();
	
	float deltaX = circPos.x - max(_position.x, min(circPos.x, _position + _size.x));
	float deltaY = circPos.y - max(_position.y, min(circPos.y, _position + _size.y));
	
	return (deltaX * deltaX + deltaY * deltaY) < circRadius * circRadius;
}

bool BoundingBox::CheckCollide_Edge(EdgeActor* edge) {

}

bool BoundingBox::CheckCollide_BoundingBox(BoundingBox* bounds) {

}

void BoundingBox::Render() {
	sf2d_draw_rectangle(_position.x, _position.y, _size.x, _size.y, RGBA8(0, 0, 0, 0));
}