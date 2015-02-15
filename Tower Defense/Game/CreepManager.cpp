#include "CreepManager.h"

#include <Game/GameScene.h>

CreepManager::CreepManager(GameScene* scene, int initialNum)
{
	for (int i = 0; i < initialNum; i++)
	{
		creeps_.push_back(new Creep(scene));		
	}
}

CreepManager::~CreepManager()
{

}

int CreepManager::GetFirstInactive()
{
	for (int i = 0; i < (int)creeps_.size(); i++)
	{
		if (!creeps_[i]->active && std::find(spawnQ_.begin(), spawnQ_.end(), i) == spawnQ_.end())
			return i;
	}
	return -1;
}

void CreepManager::LoadCreepData(const std::string& name)
{
	gfx->LoadTexture("Data/creeps/" + name + ".png", "creep_" + name);
	creepDatas_[name] = CreepData();

	std::ifstream file;
	file.open("Data/creeps/" + name + ".txt");

	std::string key;

	while (!file.eof())
	{	
		file >> key;
		if (key == "Health")
			file >> creepDatas_[name].health;
		else if (key == "Attack")
			file >> creepDatas_[name].attack;
		else if (key == "Reward")
			file >> creepDatas_[name].reward;
		else if (key == "Speed")
			file >> creepDatas_[name].speed;
		else if (key == "HBWidth")
			file >> creepDatas_[name].hbWidth;
		else if (key == "HBHeight")
			file >> creepDatas_[name].hbHeight;
		else if (key == "HBOffsetX")
			file >> creepDatas_[name].hbOffset.x_;
		else if (key == "HBOffsetY")
			file >> creepDatas_[name].hbOffset.y_;
		else if (key == "OffsetX")
			file >> creepDatas_[name].offset.x_;
		else if (key == "OffsetY")
			file >> creepDatas_[name].offset.y_;
	}
	file.close();
}

int CreepManager::NewCreep(const std::string& type, int path)
{
	int index = GetFirstInactive();
	Creep* creep = creeps_[index];
	creep->SetOffset(creepDatas_[type].offset);
	creep->Reset("creep_" + type, path);
	creep->SetAnimations(creepDatas_[type].idleAnim, creepDatas_[type].moveAnim, creepDatas_[type].attackAnim);
	creep->SetStats(creepDatas_[type].health, creepDatas_[type].attack, creepDatas_[type].reward, creepDatas_[type].speed);
	creep->SetHitbox(creepDatas_[type].hbOffset.x_, creepDatas_[type].hbOffset.y_, creepDatas_[type].hbWidth, creepDatas_[type].hbHeight);
	return index;
}

void CreepManager::QCreep(const std::string& type, int path)
{
	spawnQ_.push_back(NewCreep(type, path));
}

int CreepManager::QRandom(int path)
{
	auto iter = creepDatas_.begin();
	std::advance(iter, rand() % creepDatas_.size());
	QCreep(iter->first, path);
	return iter->second.reward;
}

Creep* CreepManager::GetColliding(const Rect& hitbox)
{
	for (int i = 0; i < (int)creeps_.size(); i++)
	{
		if (!creeps_[i]->active)
			continue;

		if (hitbox.Intersects(creeps_[i]->GetHitbox()))
			return creeps_[i];		
	}
	return nullptr;
}

Creep* CreepManager::GetFirstWithin(float range, const Vec2& position)
{
	Creep* closest = nullptr;
	float closestDist2 = range * range;
	for (int i = 0; i < (int)creeps_.size(); i++)
	{
		Creep* creep = creeps_[i];
		if (!creep->active)
			continue;
		float dist2 = (creep->GetPosition() - position).Length2();
		if (dist2 < closestDist2)
		{	
			closest = creep;
			closestDist2 = dist2;
		}
	}
	return closest;
}

bool CreepManager::AllDead()
{
	if (!spawnQ_.empty())
		return false;
	for (int i = 0; i < creeps_.size(); i++)
	{
		if (creeps_[i]->active)
			return false;
	}
	return true;
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
	if (!spawnQ_.empty())
	{
		spawnCD_ -= world->GetFDelta();
		if (spawnCD_ <= 0.f)
		{
			creeps_[spawnQ_.front()]->active = true;
			spawnQ_.pop_front();
			spawnCD_ = spawnDelay_;
		}
	}

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