#pragma once

#include <World/Scene.h>

class GameScene;

class Creep : public Entity
{
protected:
	GameScene* gScene_ = nullptr;

	int path_ = 0;
	int pathIndex_ = 0;
	Vec2 pathPoint_;

	int health_ = 0;
	int maxHealth_ = 0;
	int damage_ = 0;
	int reward_ = 0;
	float speed_ = 0.f;

	Rect healthBar_;

	int idleAnim_ = 0;
	int moveAnim_ = 0;
	int attackAnim_ = 0;

	float slowMult_ = 1.0f;
	float slowTime_ = 0.0f;

public:
	bool active = false;

	Creep(GameScene* scene, const std::string& textureID = "", int path = 0);
	~Creep();

	int GetReward(){ return reward_; }

	void Reset(const std::string& textureID = "", int path = 0);
	void SetAnimations(int idle, int move, int attack);
	void SetStats(int health, int damage, int reward, float speed);

	void Hurt(int amount){ health_ -= amount; }
	void Slow(float mult, float time){ slowMult_ = mult; slowTime_ = time; }

	void Update(float delta) override;
	void FixedUpdate() override;

	void Draw(float interp) override;
};