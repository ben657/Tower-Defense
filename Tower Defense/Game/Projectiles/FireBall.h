#pragma once

#include <Game/Projectile.h>

class FireBall : public Projectile
{
public:
	FireBall(GameScene* scene);
	~FireBall(){};

	void Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction) override;
	void FixedUpdate() override;
};
