#include "Map.h"

Map::Map(Scene* scene, const std::string& name) : Entity(), name_(name)
{
	gfx->LoadTexture("Data/maps/" + name + "/colour.png", name + "colour");
	gfx->LoadTexture("Data/maps/" + name + "/placement.png", name + "placement");
	textureID_ = name + "colour";
}

bool Map::CanPlace(const Vec2& position)
{
	Colour mask = gfx->PixelAt(position, name_ + "placement");
	return (mask.r == 0 && mask.g == 0 && mask.b == 0);
}

void Map::Draw()
{
	gfx->ClipBlit(position_ - world->camPos, textureID_, 0, 0);
}