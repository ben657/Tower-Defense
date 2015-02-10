#include "Creep.h"
#include <Game/GameScene.h>

Creep::Creep(GameScene* scene, const std::string& textureID, int path) : Entity(), gScene_(scene), path_(path)
{

}

Creep::~Creep()
{
}

void Creep::Reset(const std::string& textureID, int path)
{
	textureID_ = textureID;
	path_ = path;

	pathIndex_ = 0;
	pathPoint_ = gScene_->GetPoint(path_, 0);
	position_ = pathPoint_;
}

void Creep::SetAnimations(int idle, int move, int attack)
{
	idleAnim_ = idle;
	moveAnim_ = move;
	attackAnim_ = attack;
}

void Creep::SetStats(int health, int damage, float speed)
{
	health_ = health;
	damage_ = damage;
	speed_ = speed;
}

void Creep::Update(float delta)
{
	if (!active)
		return;

	Entity::Update(delta);
}

void Creep::FixedUpdate()
{
	if (!active)
		return;

	Vec2 direction = pathPoint_ - position_;
	direction.Normalise();

	position_ += direction * speed_;

	float dist2 = (pathPoint_ - position_).Length();

	if (dist2 < .4f)
	{
		position_ = pathPoint_;

		pathPoint_ = gScene_->NextPoint(path_, pathIndex_);
		pathIndex_++;
	}
}

void Creep::Draw()
{
	if (!active)
		return;

	Entity::Draw();
}