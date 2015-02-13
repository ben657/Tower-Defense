#include "Entity.h"
#include <World/Scene.h>

Entity::Entity(const Vec2& position, const std::string& textureID) : position_(position), textureID_(textureID)
{
}

Entity::~Entity()
{	
}

void Entity::SetHitbox(int x, int y, int width, int height)
{
	hitbox_ = Rect(0, 0, width, height);
	hitboxOffset_ = Vec2(x, y);
}

Rect& Entity::GetHitbox()
{
	hitbox_.MoveTo(position_.x_ + hitboxOffset_.x_, position_.y_ + hitboxOffset_.y_);
	return hitbox_;
}

void Entity::FixedUpdate()
{
	gfx->UpdateAnimation(animID_, world->GetFDelta());
}

void Entity::Draw()
{	
	Vec2 drawPos = (position_ + offset_) - world->camPos;
	
	if (animID_ < 0)
	{
		if (rotation == 0.0f)
			gfx->BlitAlpha(drawPos, textureID_);
		else
			gfx->Blit(drawPos, textureID_, rotation);
	}
	else
		gfx->BlitAnimated(drawPos, textureID_, animID_);

	if (drawhb)
	{
		Rect hb = GetHitbox();
		hb.MoveTo(drawPos.x_, drawPos.y_);
		gfx->BlitLine(Vec2(hb.left_, hb.top_), Vec2(hb.right_, hb.top_), Colour(255, 0, 0));
		gfx->BlitLine(Vec2(hb.left_, hb.top_), Vec2(hb.left_, hb.bottom_), Colour(255, 0, 0));
		gfx->BlitLine(Vec2(hb.right_, hb.top_), Vec2(hb.right_, hb.bottom_), Colour(255, 0, 0));
		gfx->BlitLine(Vec2(hb.left_, hb.bottom_), Vec2(hb.right_, hb.bottom_), Colour(255, 0, 0));
	}
}