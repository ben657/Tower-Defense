#pragma once

#include <Game/Projectile.h>

class FireBall : public Projectile
{
public:
	FireBall(GameScene* scene);
	~FireBall(){};

	void Reset(const std::string& textureID = "", const Vec2& position = Vec2(0.f, 0.f), const Vec2& direction = Vec2(0.f, 0.f), const char* data = nullptr) override;
	void FixedUpdate() override;
	void Draw() override;
};

