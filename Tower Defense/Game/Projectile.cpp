#include "Projectile.h"

#include <Game/GameScene.h>

Projectile::Projectile(GameScene* scene, const std::string& textureID) : Entity(Vec2(0.f, 0.f)), gScene_(scene)
{
	cm_ = gScene_->GetCM();
}

Projectile::~Projectile()
{
}

void Projectile::Reset(const std::string& textureID, const Vec2& position, const Vec2& direction, const char* data)
{
	textureID_ = textureID;
	position_ = position;
	direction_ = direction.Normalised();
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