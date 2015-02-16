#include "ProjectileManager.h"


ProjectileManager::ProjectileManager(GameScene* scene, int initialNum)
{
	for (int i = 0; i < initialNum; i++)
	{
		projs_["fireBall"].push_back((Projectile*)new FireBall(scene));
		projs_["lightning"].push_back((Projectile*) new Lightning(scene));
	}
}

ProjectileManager::~ProjectileManager()
{
}

Projectile* ProjectileManager::GetFirstInactive(const std::string& type)
{
	for (int i = 0; i < projs_[type].size(); i++)
	{
		Projectile* p = projs_[type][i];
		if (!p->active)
			return p;
	}
	return nullptr;
}

void ProjectileManager::NewProjectile(const std::string& type, const Vec2& position, const Vec2& target, const Vec2& direction)
{
	Projectile* projectile = GetFirstInactive(type);

	if (projectile == nullptr)
	{
		HAPI->DebugText("ALL PROJECTILES IN USE!!");
		return;
	}

	projectile->active = true;
	projectile->Reset("proj_" + type, position, target, direction);
}

void ProjectileManager::Update(float delta)
{
	for (auto proj : projs_)
	{
		for (int i = 0; i < proj.second.size(); i++)
		{
			if (proj.second[i]->active)
				proj.second[i]->Update(delta);
		}
	}
}

void ProjectileManager::FixedUpdate()
{
	for (auto proj : projs_)
	{
		for (int i = 0; i < proj.second.size(); i++)
		{
			if (proj.second[i]->active)
				proj.second[i]->FixedUpdate();
		}
	}
}

void ProjectileManager::Draw(float interp)
{
	for (auto proj : projs_)
	{
		for (int i = 0; i < proj.second.size(); i++)
		{
			if (proj.second[i]->active)
				proj.second[i]->Draw(interp);
		}
	}
}
