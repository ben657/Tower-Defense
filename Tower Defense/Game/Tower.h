#pragma once

#include <World/Entity.h>
#include <Game/CreepManager.h>
#include <Game/ProjectileManager.h>

class GameScene;

class Tower : public Entity
{
private:
	GameScene* gScene_ = nullptr;
	CreepManager* cm_ = nullptr;
	ProjectileManager* pm_ = nullptr;

	int health_ = 0;
	int damage_ = 0;
	float range_ = 0.f;
	float attackDelay_ = 0.f;

	int idleAnim_ = 0;
	int fireAnim_ = 0;

	float attackCD_ = 0.f;

public:
	bool active = false;

	Tower(GameScene* scene, const std::string& textureID = "");
	~Tower();

	void Reset(const std::string& textureID = "", const Vec2& position = Vec2(0.f, 0.f));
	void SetAnimations(int idle, int fire);
	void SetStats(int health, int damage, float attackDelay, float range);

	void Update(float delta) override;
	void FixedUpdate() override;

	void Draw() override;
};

