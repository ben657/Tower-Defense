#pragma once

#include <Game/Projectile.h>
#include <vector>
#include <map>

struct ProjectileData
{
	int health = 0;
	int damage = 0;
	float speed = 0.f;
	Vec2 offset;
	int anim = -1;
};

class ProjectileManager
{
private:
	std::map<std::string, ProjectileData> projDatas_;
	std::vector<Projectile*> projs_;

	Projectile* GetFirstInactive();

public:
	ProjectileManager(int initialNum);
	~ProjectileManager();

	void NewProjectile(const std::string& type, const Vec2& position, const Vec2& direction);

	void Update(float delta);
	void FixedUpdate();
	void Draw();
};

