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
	hitboxOffset_ = Vec2((float)x, (float)y);
}

Rect& Entity::GetHitbox()
{
	hitbox_.MoveTo((int)position_.x_ + (int)hitboxOffset_.x_, (int)position_.y_ + (int)hitboxOffset_.y_);
	return hitbox_;
}

void Entity::FixedUpdate()
{
	lastPosition_ = position_;
	gfx->UpdateAnimation(animID_, world->GetFDelta());
}

void Entity::Draw(float interp)
{	
	Vec2 iPos = lastPosition_ + (position_ - lastPosition_) * interp;
	Vec2 drawPos = (iPos + offset_) - world->camPos;
	
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
		Vec2 hbPos = (position_ + hitboxOffset_) - world->camPos;
		hb.MoveTo((int)hbPos.x_, (int)hbPos.y_);
		gfx->BlitLine(Vec2((float)hb.left_, (float)hb.top_), Vec2((float)hb.right_, (float)hb.top_), Colour(255, 0, 0));
		gfx->BlitLine(Vec2((float)hb.left_, (float)hb.top_), Vec2((float)hb.left_, (float)hb.bottom_), Colour(255, 0, 0));
		gfx->BlitLine(Vec2((float)hb.right_, (float)hb.top_), Vec2((float)hb.right_, (float)hb.bottom_), Colour(255, 0, 0));
		gfx->BlitLine(Vec2((float)hb.left_, (float)hb.bottom_), Vec2((float)hb.right_, (float)hb.bottom_), Colour(255, 0, 0));
	}
}