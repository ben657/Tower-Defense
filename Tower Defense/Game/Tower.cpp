#include "Tower.h"


Tower::Tower(GameScene* scene, const std::string& textureID = "") : Entity((Scene*)scene, Vec2(0.f, 0.f), textureID), gScene_(scene)
{

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

void Tower::SetStats(int health, int damage, int attackDelay)
{
	health_ = health;
	damage_ = damage;
	attackDelay_ = attackDelay;
}

void Tower::Update(float delta)
{
	if (!active)
		return;

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