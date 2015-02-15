#include "TowerManager.h"

TowerManager::TowerManager(GameScene* scene, int initialNum)
{
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

void TowerManager::LoadTowerData(const std::string& name)
{
	gfx->LoadTexture("Data/towers/" + name + ".png", "tower_" + name);
	gfx->LoadTexture("Data/icons/" + name + ".png", "icon_" + name);
	towerDatas_[name] = TowerData();
	towerTypes_.push_back(name);

	std::ifstream file;
	file.open("Data/towers/" + name + ".txt");

	std::string key;

	while (!file.eof())
	{
		file >> key;
		if (key == "Health")
			file >> towerDatas_[name].health;
		else if (key == "Attack")
			file >> towerDatas_[name].attack;
		else if (key == "Cost")
			file >> towerDatas_[name].cost;
		else if (key == "Range")
			file >> towerDatas_[name].range;
		else if (key == "ProjType")
			file >> towerDatas_[name].projType;
		else if (key == "AttackDelay")
			file >> towerDatas_[name].attackDelay;
		else if (key == "HBWidth")
			file >> towerDatas_[name].hbWidth;
		else if (key == "HBHeight")
			file >> towerDatas_[name].hbHeight;
		else if (key == "HBOffsetX")
			file >> towerDatas_[name].hbOffset.x_;
		else if (key == "HBOffsetY")
			file >> towerDatas_[name].hbOffset.y_;
		else if (key == "OffsetX")
			file >> towerDatas_[name].offset.x_;
		else if (key == "OffsetY")
			file >> towerDatas_[name].offset.y_;
	}
	file.close();
}

void TowerManager::NewTower(const std::string& type, const Vec2& position)
{
	Tower* tower = GetFirstInactive();
	tower->SetOffset(towerDatas_[type].offset);
	tower->active = true;
	tower->Reset("tower_" + type, position);
	tower->SetAnimations(towerDatas_[type].idleAnim, towerDatas_[type].fireAnim);
	tower->SetStats(towerDatas_[type].health, towerDatas_[type].attack, towerDatas_[type].attackDelay, towerDatas_[type].range, towerDatas_[type].projType);
	tower->SetHitbox(towerDatas_[type].hbOffset.x_, towerDatas_[type].hbOffset.y_, towerDatas_[type].hbWidth, towerDatas_[type].hbHeight);
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