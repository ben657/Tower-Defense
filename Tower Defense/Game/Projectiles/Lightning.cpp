#include "Lightning.h"
#include <Game/GameScene.h>

Lightning::Lightning(GameScene* scene) : Projectile(scene)
{
	SetOffset(Vec2(-8.f, -8.f));
	SetHitbox(-8.f, -.8f, 16.f, 16.f);
	damage_ = 1;
}

Lightning::~Lightning()
{
}

void Lightning::Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction)
{
	Projectile::Reset(textureID, position, target, direction);

	timeActive_ = 0.0f;
	colour_.g = 255 - rand() % 150;

	Rect hb = GetHitbox();
	hb.MoveTo(target.x_, target.y_);

	Creep* hit = cm_->GetColliding(hb);
	if (hit != nullptr)
	{
		hit->Hurt(damage_);

		hit->active = false;

		Creep* next = cm_->GetFirstWithin(100, target_);
		if (next != nullptr)
			gScene_->GetPM()->NewProjectile("lightning", target_, next->GetPosition(), (next->GetPosition() - target_).Normalised());
		
		hit->active = true;
	}	
}

void Lightning::FixedUpdate()
{
	timeActive_ += world->GetFDelta();
	if (timeActive_ >= 200)
		active = false;
}

void Lightning::Draw()
{
	Vec2 startPos = (position_) - world->camPos;
	Vec2 endPos = target_ - world->camPos;

	gfx->BlitLine(startPos, endPos, colour_);
}

