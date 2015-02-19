#pragma once

#include <Game/Projectile.h>

class Glue : public Projectile
{
private:
	float stayTime_ = 5000.0f;
	float timeOut_ = 0.0f;

	bool moving_ = true;

public:
	Glue(GameScene* scene);
	~Glue(){};

	void Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction) override;
	void FixedUpdate() override;
};