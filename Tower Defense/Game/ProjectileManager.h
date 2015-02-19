#pragma once

#include <Game/Projectile.h>

#include <Game/Projectiles/FireBall.h>
#include <Game/Projectiles/Lightning.h>
#include <Game/Projectiles/Glue.h>

#include <vector>
#include <map>

class ProjectileManager
{
private:
	std::map<std::string, std::vector<Projectile*>> projs_;

	Projectile* GetFirstInactive(const std::string& type);

public:
	ProjectileManager(GameScene* scene, int initialNum);
	~ProjectileManager();

	void NewProjectile(const std::string& type, const Vec2& position, const Vec2& target, const Vec2& direction);

	void Update(float delta);
	void FixedUpdate();
	void Draw(float interp);
};

