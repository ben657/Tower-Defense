#include "Projectile.h"

Projectile::Projectile(const std::string& textureID) : Entity(Vec2(0.f, 0.f))
{
}

Projectile::~Projectile()
{
}

void Projectile::Reset(const std::string& textureID, const Vec2& position, const Vec2& direction)
{
	textureID_ = textureID;
	position_ = position;
	direction_ = direction.Normalised();
}

void Projectile::SetStats(int health, int damage, float speed)
{
	health_ = health;
	damage_ = damage;
	speed_ = speed;
}

void Projectile::Update(float delta)
{
	if (!active)
		return;

	Entity::Update(delta);
}

void Projectile::FixedUpdate()
{
	if (!active)
		return;

	position_ += direction_ * speed_;
}

void Projectile::Draw()
{
	if (!active)
		return;

	Entity::Draw();
}