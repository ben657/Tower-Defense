#include "Bunny.h"

Bunny::Bunny(int x, int y, int path) : Creep(x, y, "bunny", path)
{
	offset_ = Vec2(-16.f, -16.f);
	health_ = 10;
	damage_ = 2;
	speed_ = 0.3f;
}

Bunny::~Bunny()
{
}
