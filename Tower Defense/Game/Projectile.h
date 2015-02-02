#pragma once

#include <World/Entity.h>

class Projectile : public Entity
{
private:
	int health_ = 0;
	int damage_ = 0;	
	float speed_ = 0.f;	
	Vec2 direction_;	

public:
	bool active = false;

	Projectile(const std::string& textureID = "");
	~Projectile();

	void Reset(const std::string& textureID = "", const Vec2& position = Vec2(0.f, 0.f), const Vec2& direction = Vec2(0.f, 0.f));
	void SetStats(int health, int damage, float speed);

	void Update(float delta) override;
	void FixedUpdate() override;

	void Draw() override;
};

