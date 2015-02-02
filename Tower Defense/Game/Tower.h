#pragma once

#include <World/Entity.h>

class GameScene;

class Tower : public Entity
{
private:
	GameScene* gScene_ = nullptr;

	int health_ = 0;
	int damage_ = 0;
	float attackDelay_ = 0.f;

	int idleAnim_ = 0;
	int fireAnim_ = 0;

public:
	bool active = false;

	Tower(GameScene* scene, const std::string& textureID = "");
	~Tower();

	void Reset(const std::string& textureID = "", const Vec2& position = Vec2(0.f, 0.f));
	void SetAnimations(int idle, int fire);
	void SetStats(int health, int damage, int attackDelay);

	void Update(float delta) override;
	void FixedUpdate() override;

	void Draw() override;
};

