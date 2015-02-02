#include "ProjectileManager.h"


ProjectileManager::ProjectileManager(int initialNum)
{
	//Temp data, will read from file eventually
	projDatas_["fireBall"] = ProjectileData();
	projDatas_["fireBall"].health = 10;
	projDatas_["fireBall"].damage = 2;
	projDatas_["fireBall"].speed = 5.f;
	projDatas_["fireBall"].offset = Vec2(-16.f, -16.f);

	for (int i = 0; i < initialNum; i++)
	{
		projs_.push_back(new Projectile());
	}
}

ProjectileManager::~ProjectileManager()
{
}

Projectile* ProjectileManager::GetFirstInactive()
{
	for (int i = 0; i < (int)projs_.size(); i++)
	{
		if (!projs_[i]->active)
			return projs_[i];
	}
}

void ProjectileManager::NewProjectile(const std::string& type, const Vec2& position, const Vec2& direction)
{
	Projectile* projectile = GetFirstInactive();
	projectile->SetOffset(projDatas_[type].offset);
	projectile->active = true;
	projectile->Reset("proj_" + type, position, direction);
	projectile->SetAnimID(projDatas_[type].anim);
	projectile->SetStats(projDatas_[type].health, projDatas_[type].damage, projDatas_[type].speed);
}

void ProjectileManager::Update(float delta)
{
	for (Projectile* projectile : projs_)
	{
		if (projectile->active)
			projectile->Update(delta);
	}
}

void ProjectileManager::FixedUpdate()
{
	for (Projectile* projectile : projs_)
	{
		if (projectile->active)
			projectile->FixedUpdate();
	}
}

void ProjectileManager::Draw()
{
	for (Projectile* projectile : projs_)
	{
		if (projectile->active)
			projectile->Draw();
	}
}
