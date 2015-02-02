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
	int damage_ = 0;
	float speed_ = 0.f;

	int idleAnim_ = 0;
	int moveAnim_ = 0;
	int attackAnim_ = 0;

public:
	bool active = false;

	Creep(GameScene* scene, const std::string& textureID = "", int path = 0);
	~Creep();

	void Reset(const std::string& textureID = "", int path = 0);
	void SetAnimations(int idle, int move, int attack);
	void SetStats(int health, int damage, float speed);

	void Update(float delta) override;
	void FixedUpdate() override;

	void Draw() override;
};