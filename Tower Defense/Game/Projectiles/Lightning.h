#pragma once
#include <Game/Projectile.h>

class Lightning : public Projectile
{
private:
	float timeActive_ = 0.0f;
	Colour colour_ = Colour(0, 255, 255);

public:
	Lightning(GameScene* scene);
	~Lightning();

	void Reset(const std::string& textureID, const Vec2& position, const Vec2& target, const Vec2& direction) override;
	void FixedUpdate() override;
	void Draw(float interp) override;
};