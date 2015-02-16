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

void Creep::SetStats(int health, int damage, int reward, float speed)
{
	health_ = health;
	damage_ = damage;
	reward_ = reward;
	speed_ = speed;
}

void Creep::Update(float delta)
{
	if (!active)
		return;
}

void Creep::FixedUpdate()
{
	if (!active)
		return;

	if (health_ <= 0)
	{
		active = false;
		gScene_->AddMoney(reward_);
		return;
	}

	Vec2 direction = pathPoint_ - position_;
	direction.Normalise();

	position_ += direction * speed_;

	float dist2 = (pathPoint_ - position_).Length();

	if (dist2 < 1.f)
	{
		position_ = pathPoint_;
		
		Vec2 nextp = gScene_->NextPoint(path_, pathIndex_);

		if (gScene_->LastPoint(path_, pathIndex_))
		{
			gScene_->RemHealth(damage_);
			active = false;
			return;
		}

		pathPoint_ = nextp;
		
		pathIndex_++;
	}

	Entity::FixedUpdate();
}

void Creep::Draw(float interp)
{
	if (!active)
		return;

	Entity::Draw(interp);
}