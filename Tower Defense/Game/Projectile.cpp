#include "Projectile.h"

#include <Game/GameScene.h>

Projectile::Projectile(GameScene* scene, const std::string& textureID) : Entity(Vec2(0.f, 0.f)), gScene_(scene)
{
	cm_ = gScene_->GetCM();
}

Projectile::~Projectile()
{
}

void Projectile::Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction)
{
	textureID_ = textureID;
	position_ = position;
	target_ = target;
	direction_ = direction;
}

void Projectile::Update(float delta)
{
	if (!active)
		return;	
}

void Projectile::FixedUpdate()
{
	if (!active)
		return;
}

void Projectile::Draw()
{
	if (!active)
		return;

	Entity::Draw();
}