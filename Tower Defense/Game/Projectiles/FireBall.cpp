#include "FireBall.h"

FireBall::FireBall(GameScene* scene) : Projectile(scene)
{
	SetOffset(Vec2(-16.f, -16.f));
	SetHitbox(-8, -8, 16, 16);
	animID_ = gfx->CreateAnimation(0, 3, 32, 32, 4, 1, 4);
	health_ = 10;
	damage_ = 10;
	speed_ = 4.f;
}

void FireBall::FixedUpdate()
{
	Projectile::FixedUpdate();

	if (!active)
		return;

	position_ += direction_ * speed_;

	Creep* hit = cm_->GetColliding(GetHitbox());
	if (hit != nullptr)
	{
		hit->Hurt(damage_);
		active = false;
		return;
	}

	Vec2 screenPos = position_ - world->camPos;
	if (screenPos.x_ < 0 + offset_.x_ || screenPos.x_ > gfx->GetWidth() - offset_.x_ ||
		screenPos.y_ < 0 + offset_.y_ || screenPos.y_ > gfx->GetHeight() - offset_.y_)
		active = false;

	Entity::FixedUpdate();
}