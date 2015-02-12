#pragma once

#include <World/Entity.h>
#include <Game/CreepManager.h>

class GameScene;

class Projectile : public Entity
{
protected:
	GameScene* gScene_ = nullptr;

	int health_ = 0;
	int damage_ = 0;	
	float speed_ = 0.f;	
	Vec2 direction_;	

	CreepManager* cm_ = nullptr;

public:
	bool active = false;

	Projectile(GameScene* scene, const std::string& textureID = "");
	virtual ~Projectile();

	virtual void Reset(const std::string& textureID = "", const Vec2& position = Vec2(0.f, 0.f), const Vec2& direction = Vec2(0.f, 0.f), const char* data = nullptr);

	void Update(float delta) override;
	void FixedUpdate() override;

	void Draw() override;
};

