#include "FireBall.h"

FireBall::FireBall(GameScene* scene) : Projectile(scene)
{
	SetOffset(Vec2(-8.f, -8.f));
	SetHitbox(-8.f, -.8f, 16.f, 16.f);
	health_ = 10;
	damage_ = 10;
	speed_ = 5.f;
}

void FireBall::Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction)
{
	Projectile::Reset(textureID, position, target, direction);
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

	if (position_.x_ < 0 + offset_.x_ || position_.x_ > 1600 - offset_.x_ || 
		position_.y_ < 0 + offset_.y_ || position_.y_ > 900 - offset_.y_)
		active = false;

	Entity::FixedUpdate();
}