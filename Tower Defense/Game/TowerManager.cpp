#include "TowerManager.h"


TowerManager::TowerManager(GameScene* scene, int initialNum)
{
	//Temp data, will read from file eventually
	towerDatas_["fireBall"] = TowerData();
	towerDatas_["fireBall"].health = 10;
	towerDatas_["fireBall"].attack = 2;
	towerDatas_["fireBall"].attackDelay = 0.5f;
	towerDatas_["fireBall"].offset = Vec2(-16.f, -16.f);

	for (int i = 0; i < initialNum; i++)
	{
		towers_.push_back(new Tower(scene));
	}
}

TowerManager::~TowerManager()
{
}

Tower* TowerManager::GetFirstInactive()
{
	for (int i = 0; i < (int)towers_.size(); i++)
	{
		if (!towers_[i]->active)
			return towers_[i];
	}
	return nullptr;
}

void TowerManager::NewTower(const std::string& type, const Vec2& position)
{
	Tower* tower = GetFirstInactive();
	tower->SetOffset(towerDatas_[type].offset);
	tower->active = true;
	tower->Reset("tower_" + type, position);
	tower->SetAnimations(towerDatas_[type].idleAnim, towerDatas_[type].fireAnim);
	tower->SetStats(towerDatas_[type].health, towerDatas_[type].attack, towerDatas_[type].attackDelay, towerDatas_[type].range);
}

void TowerManager::Update(float delta)
{
	for (Tower* tower : towers_)
	{
		if (tower->active)
			tower->Update(delta);
	}
}

void TowerManager::FixedUpdate()
{
	for (Tower* tower : towers_)
	{
		if (tower->active)
			tower->FixedUpdate();
	}
}

void TowerManager::Draw()
{
	for (Tower* tower : towers_)
	{
		if (tower->active)
			tower->Draw();
	}
}