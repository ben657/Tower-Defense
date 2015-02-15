#include "GameScene.h"

GameScene::GameScene(const std::string& mapName)
{
	gfx->LoadTexture("Data/projectiles/fireBall.png", "proj_fireBall");
	gfx->LoadTexture("Data/icons/tower.png", "icon_tower");	
}

GameScene::~GameScene()
{

}

void GameScene::SwitchedTo(const std::string& from, void* data)
{
	std::string mapName = std::string((char*)data);

	srand(time(0));

	cManager_ = new CreepManager(this, 1000);
	pManager_ = new ProjectileManager(this, 100);
	tManager_ = new TowerManager(this, 100);

	map = new Map((Scene*)this, mapName);

	cManager_->LoadCreepData("bunny");
	cManager_->LoadCreepData("unicorn");

	tManager_->LoadTowerData("fireBall");
	tManager_->LoadTowerData("lightning");

	std::ifstream pathFile;
	pathFile.open("Data/maps/" + mapName + "/paths.txt");

	pathFile >> numPaths;
	paths_.resize(numPaths);
	for (int i = 0; i < numPaths; i++)
	{
		int l;
		pathFile >> l;
		pathLengths_.push_back(l);
	}

	for (int i = 0; i < numPaths; i++)
	{
		for (int j = 0; j < pathLengths_[i]; j++)
		{
			int x = 0;
			int y = 0;
			pathFile >> x;
			pathFile >> y;
			paths_[i].push_back(Vec2((float)x, (float)y));
		}
	}

	pathFile.close();

	towerMenuBtn = new Button(Rect(0, gfx->GetHeight() - 64, 64, 64), "Towers", Colour(255, 0, 0));
	towerMenuBtn->iconOffset_ = Vec2(4.f, 4.f);
	towerMenuBtn->SetTextureID("icon_tower");
	AddEntity(towerMenuBtn);
	for (int i = 0; i < tManager_->towerTypes_.size(); i++)
	{
		Button* twrBtn = new Button(Rect(74 + (i)* 58, gfx->GetHeight() - 32 - 24, 48, 48), "tower", Colour(0, 0, 255));
		twrBtn->visible_ = false;
		twrBtn->iconOffset_ = Vec2(4.f, 4.f);
		twrBtn->SetTextureID("icon_" + tManager_->towerTypes_[i]);
		AddEntity(twrBtn);
		towerBtns.push_back(twrBtn);
	}

	SpawnWave();
}

void GameScene::SpawnWave()
{
	numCreeps = 0;
	wave++;
	int maxDifficulty = wave * 500;
	int waveDifficulty = 0;
	cManager_->spawnDelay_ = 100.f;
	while (waveDifficulty < maxDifficulty)
	{
		numCreeps++;
		waveDifficulty += cManager_->QRandom(rand() % numPaths);
	}
}

Vec2 GameScene::NextPoint(int path, int currentIndex)
{
	int foo = 25;	
	if (currentIndex + 1 >= pathLengths_[path])
		return paths_[path][pathLengths_[path] - 1];
	Vec2 point = paths_[path][currentIndex + 1];
	point.x_ += -foo + rand() % foo * 2;
	point.y_ += -foo + rand() % foo * 2;
	return point;
}

void GameScene::Update(float delta)
{
	Scene::Update(delta);	

	if (input->MouseBtnJustDown(0) && placingTower != "")
	{
		Vec2 pos = input->MousePos() + world->camPos;
		if (map->CanPlace(pos))
		{
			tManager_->NewTower(placingTower, pos);
			placingTower = "";
		}
	}

	if (towerMenuBtn->justPressed_)
	{
		for (int i = 0; i < towerBtns.size(); i++)
		{
			towerBtns[i]->visible_ = !towerBtns[i]->visible_;
		}
	}

	for (int i = 0; i < towerBtns.size(); i++)
	{
		if (towerBtns[i]->justPressed_)
		{
			placingTower = tManager_->towerTypes_[i];
			break;
		}
	}

	if (input->KeyDown('A'))
	{
		world->camPos.x_ -= 2;
	}
	if (input->KeyDown('D'))
	{
		world->camPos.x_ += 2;
	}
	if (input->KeyDown('W'))
	{
		world->camPos.y_ -= 2;
	}
	if (input->KeyDown('S'))
	{
		world->camPos.y_ += 2;
	}

	if (input->KeyJustDown('1'))
	{
		world->ChangeSpeedMult(1.f);
	}
	if (input->KeyJustDown('2'))
	{
		world->ChangeSpeedMult(2.f);
	}
	if (input->KeyJustDown('3'))
	{
		world->ChangeSpeedMult(4.f);
	}
	if (input->KeyJustDown(' '))
	{
		world->ToggleFixedStep();
	}

	//replace 2048 with mapWidth, 1600 with scrWidth at some point
	//same with heights
	if (world->camPos.x_ < 0)
		world->camPos.x_ = 0;
	if (world->camPos.x_ > 2048 - 1600)
		world->camPos.x_ = 2048 - 1600;
	if (world->camPos.y_ < 0)
		world->camPos.y_ = 0;
	if (world->camPos.y_ > 1024 - 900)
		world->camPos.y_ = 1024 - 900;	

	tManager_->Update(delta);
	cManager_->Update(delta);
	pManager_->Update(delta);
}

void GameScene::FixedUpdate()
{
	cManager_->FixedUpdate();
	tManager_->FixedUpdate();
	pManager_->FixedUpdate();
	Scene::FixedUpdate();

	if (cManager_->AllDead())
	{
		SpawnWave();
		cManager_->spawnDelay_ *= 0.9f;
	}
}

void GameScene::Draw()
{		
	map->Draw();
	cManager_->Draw();
	tManager_->Draw();
	pManager_->Draw();
	gfx->BlitText(Vec2(10, 10), "Money: " + std::to_string(plMoney), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 35), "Health: " + std::to_string(plHealth), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 60), "Wave: " + std::to_string(wave), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 85), "Creeps left: " + std::to_string(numCreeps), Colour(0, 0, 0));
	Scene::Draw();
}