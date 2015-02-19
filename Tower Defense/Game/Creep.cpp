#include "Creep.h"
#include <Game/GameScene.h>

Creep::Creep(GameScene* scene, const std::string& textureID, int path) : Entity(), gScene_(scene), path_(path)
{	
	healthBar_ = Rect(0, 0, 70, 10);
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
	maxHealth_ = health;
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
		health_ = 0;
		active = false;
		gScene_->AddMoney(reward_);
		return;
	}

	float speed = speed_;

	if (slowTime_ > 0.0f)
	{
		speed *= slowMult_;
		slowTime_ -= world->GetFDelta();
	}

	Vec2 direction = pathPoint_ - position_;
	direction.Normalise();

	position_ += direction * speed;

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
	Rect hb = GetHitbox();
	Vec2 hbPos = position_ - Vec2(35.f, (float)hb.Height() + 5.f) - world->camPos;
	healthBar_.MoveTo((int)hbPos.x_, (int)hbPos.y_);
	healthBar_.right_ = healthBar_.left_ + 70;

	//Blit red bar underneath
	gfx->BlitRect(healthBar_, Colour(255, 0, 0));
	float percLeft = (float)health_ / (float)maxHealth_;
	if (percLeft <= 0)
		return;
	healthBar_.right_ = (int)(healthBar_.left_ + 70 * percLeft);

	//Blit green bar at length depending on health
	gfx->BlitRect(healthBar_, Colour(0, 255, 0));
}