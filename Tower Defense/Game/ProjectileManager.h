#pragma once

#include <Game/Projectile.h>

#include <Game/Projectiles/FireBall.h>

#include <vector>
#include <map>

struct ProjectileData
{
	int health = 0;
	int damage = 0;
	float speed = 0.f;
	int hbWidth = 0;
	int hbHeight = 0;
	Vec2 hbOffset;
	Vec2 offset;
	int anim = -1;
};

class ProjectileManager
{
private:
	std::map<std::string, std::vector<Projectile*>> projs_;

	Projectile* GetFirstInactive(const std::string& type);

public:
	ProjectileManager(GameScene* scene, int initialNum);
	~ProjectileManager();

	void NewProjectile(const std::string& type, const Vec2& position, const Vec2& direction, const char* data = nullptr);

	void Update(float delta);
	void FixedUpdate();
	void Draw();
};

