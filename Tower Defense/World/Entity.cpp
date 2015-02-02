#include "Entity.h"
#include <World/Scene.h>

Entity::Entity(Scene* scene, const Vec2& position, const std::string& textureID) : scene_(scene), position_(position), textureID_(textureID)
{
}

Entity::~Entity()
{	
}

void Entity::Update(float delta)
{
	gfx->UpdateAnimation(animID_, delta);
}

void Entity::Draw()
{	
	Vec2 drawPos = position_ + offset_;

	if (animID_ < 0)
	{
		if (rotation == 0.0f)
			gfx->BlitAlpha(drawPos, textureID_);
		else
			gfx->Blit(drawPos, textureID_, rotation);
	}
	else
		gfx->BlitAnimated(drawPos, textureID_, animID_);
}