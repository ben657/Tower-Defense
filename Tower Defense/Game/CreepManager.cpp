#include "CreepManager.h"

#include <Game/GameScene.h>

CreepManager::CreepManager(GameScene* scene, int initialNum)
{
	//Temp data, will read from file eventually
	creepDatas_["bunny"] = CreepData();
	creepDatas_["bunny"].health = 10;
	creepDatas_["bunny"].attack = 2;
	creepDatas_["bunny"].speed = 1.f;
	creepDatas_["bunny"].offset = Vec2(-16.f, -16.f);
	//creepDatas_["bunny"].idleAnim = gfx->CreateAnimation(0, 1, 32, 32, 2, 1, 16);

	for (int i = 0; i < initialNum; i++)
	{
		creeps_.push_back(new Creep(scene));		
	}
}

CreepManager::~CreepManager()
{

}

Creep* CreepManager::GetFirstInactive()
{
	for (int i = 0; i < (int)creeps_.size(); i++)
	{
		if (!creeps_[i]->active)
			return creeps_[i];
	}
	return nullptr;
}

void CreepManager::NewCreep(const std::string& type, int path)
{
	Creep* creep = GetFirstInactive();
	creep->SetOffset(creepDatas_[type].offset);
	creep->active = true;
	creep->Reset("creep_" + type, path);
	creep->SetAnimations(creepDatas_[type].idleAnim, creepDatas_[type].moveAnim, creepDatas_[type].attackAnim);
	creep->SetStats(creepDatas_[type].health, creepDatas_[type].attack, creepDatas_[type].speed);
}

Creep* CreepManager::GetFirstWithin(float range, const Vec2& position)
{
	for (int i = 0; i < (int)creeps_.size(); i++)
	{
		Creep* creep = creeps_[i];
		if (!creep->active)
			continue;

		if ((creep->GetPosition() - position).Length2() < range * range)
			return creep;
	}
	return nullptr;
}

void CreepManager::Update(float delta)
{
	for (Creep* creep : creeps_)
	{
		if (creep->active)
			creep->Update(delta);
	}
}

void CreepManager::FixedUpdate()
{
	for (Creep* creep : creeps_)
	{
		if (creep->active)
			creep->FixedUpdate();
	}
}

void CreepManager::Draw()
{
	for (Creep* creep : creeps_)
	{
		if (creep->active)
			creep->Draw();
	}
}