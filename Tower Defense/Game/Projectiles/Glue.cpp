#include "Glue.h"

Glue::Glue(GameScene* scene) : Projectile(scene)
{
	SetOffset(Vec2(-16.f, -16.f));
	SetHitbox(-9, -9, 18, 18);
	health_ = 10;
	damage_ = 10;
	speed_ = 5.f;
}

void Glue::Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction)
{
	Projectile::Reset(textureID, position, target, direction);
	moving_ = true;
	timeOut_ = 0.0f;
}

void Glue::FixedUpdate()
{
	Projectile::FixedUpdate();

	if (moving_)
	{
		position_ += direction_ * speed_;

		float dist2 = (target_ - position_).Length();

		if (dist2 < 3.f)
		{
			position_ = target_;
			moving_ = false;
		}

		Vec2 screenPos = position_ - world->camPos;
		if (screenPos.x_ < 0 + offset_.x_ || screenPos.x_ > gfx->GetWidth() - offset_.x_ ||
			screenPos.y_ < 0 + offset_.y_ || screenPos.y_ > gfx->GetHeight() - offset_.y_)
			active = false;
	}
	else
	{
		timeOut_ += world->GetFDelta();

		if (timeOut_ >= stayTime_)
		{
			active = false;
			return;
		}

		Creep* hit = cm_->GetColliding(GetHitbox());
		if (hit != nullptr)
		{
			hit->Slow(0.2f, 100.f);
		}
	}
}