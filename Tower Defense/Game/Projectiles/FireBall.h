#pragma once

#include <Game/Projectile.h>

class FireBall : public Projectile
{
public:
	FireBall(GameScene* scene);
	~FireBall(){};

	void FixedUpdate() override;
};
