#include "Tower.h"

#include <Game/GameScene.h>

Tower::Tower(GameScene* scene, const std::string& textureID) : Entity(Vec2(0.f, 0.f), textureID), gScene_(scene)
{
	cm_ = gScene_->GetCM();
	pm_ = gScene_->GetPM();
}

Tower::~Tower()
{
}

void Tower::Reset(const std::string& textureID, const Vec2& position)
{
	textureID_ = textureID;
	position_ = position;
}

void Tower::SetAnimations(int idle, int fire)
{
	idleAnim_ = idle;
	fireAnim_ = fire;
}

void Tower::SetStats(int health, int damage, float attackDelay, float range)
{
	health_ = health;
	damage_ = damage;
	attackDelay_ = attackDelay;
	range_ = range;
}

void Tower::Update(float delta)
{
	if (!active)
		return;

	if (attackCD_ <= 0.f)
	{
		attackCD_ = attackDelay_ * 1000.f;
		Creep* target = cm_->GetFirstWithin(range_, position_);
		if (target != nullptr)
		{
			pm_->NewProjectile("fireBall", position_, (target->GetPosition() - position_).Normalised());
		}
	}
	attackCD_ -= delta;
	

	Entity::Update(delta);
}

void Tower::FixedUpdate()
{
	if (!active)
		return;
}

void Tower::Draw()
{
	if (!active)
		return;

	Entity::Draw();
}