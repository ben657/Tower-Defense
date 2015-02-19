#include "GameScene.h"

GameScene::GameScene()
{
	gfx->LoadTexture("Data/projectiles/fireBall.png", "proj_fireBall");
	gfx->LoadTexture("Data/projectiles/tar.png", "proj_glue");
	gfx->LoadTexture("Data/icons/tower.png", "icon_tower");	

	audio->LoadSound("Data/sounds/gameLoop.wav", "gameLoop");
	audio->LoadSound("Data/sounds/newWave.wav", "newWave");
}

GameScene::~GameScene()
{
	Scene::~Scene();
	delete cManager_;
	delete pManager_;
	delete tManager_;
	if (map_ != nullptr)
		delete map_;
	if (placingTower_ != nullptr)
		delete placingTower_;
}

void GameScene::SwitchedTo(const std::string& from, void* data)
{
	HAPI->ChangeFont("Arial", 12, 700);

	std::string mapName = std::string((char*)data);

	audio->StopSound("menuLoop");
	audio->PlaySound("gameLoop", true, 1000);

	srand((int)time(0));

	plMoney = 1000;
	plHealth = 20;
	numPaths = 0;
	numCreeps = 0;
	wave = 0;

	cManager_ = new CreepManager(this, 5000);
	pManager_ = new ProjectileManager(this, 100);
	tManager_ = new TowerManager(this, 100);

	map_ = new Map((Scene*)this, mapName);

	cManager_->LoadCreepData("bunny");
	cManager_->LoadCreepData("unicorn");

	tManager_->LoadTowerData("fireBall");
	tManager_->LoadTowerData("lightning");
	tManager_->LoadTowerData("tar");

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

	towerAnim = gfx->CreateAnimation(0, 3, 32, 48, 4, 1, 8);

	towerMenuBtn = new Button(Rect(0, gfx->GetHeight() - 64, 64, 64), "Towers", Colour(255, 0, 0));
	towerMenuBtn->iconOffset_ = Vec2(4.f, 4.f);
	towerMenuBtn->SetTextureID("icon_tower");
	AddEntity(towerMenuBtn);
	for (int i = 0; i < (int)tManager_->towerTypes_.size(); i++)
	{
		Button* twrBtn = new Button(Rect(74 + (i)* 58, gfx->GetHeight() - 32 - 24, 48, 48), "tower", Colour(0, 0, 255));
		twrBtn->visible_ = false;
		twrBtn->iconOffset_ = Vec2(4.f, 4.f);
		twrBtn->SetTextureID("icon_" + tManager_->towerTypes_[i]);
		AddEntity(twrBtn);
		towerBtns.push_back(twrBtn);
	}
	
	StartSpawning();
}

void* GameScene::SwitchedFrom(const std::string& to)
{
	audio->StopSound("gameLoop");

	world->ChangeSpeedMult(1.f);
	world->camPos.Zero();

	if (to == "GameOverScene")
	{
		world->SetScore(wave - 1);
		const char* map = map_->name_.c_str();
		return (void*)map;
	}
	return nullptr;
}

void GameScene::StartSpawning()
{
	spawning_ = true;
	spawnThread_ = std::thread(&GameScene::SpawnWave, this);
}

void GameScene::SpawnWave()
{
	numCreeps = 0;
	wave++;
	int maxDifficulty = wave * 50;
	int waveDifficulty = 0;
	cManager_->spawnDelay_ = 400.f;
	while (waveDifficulty < maxDifficulty)
	{
		numCreeps++;
		waveDifficulty += cManager_->QRandom(rand() % numPaths, wave);
	}
	spawning_ = false;
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

	//if (input->KeyJustDown(HK_ESCAPE))
	//{
	//	//HAPI->Close();
	//}

	if (!spawning_ && spawnThread_.joinable())
	{
		spawnThread_.join();
		audio->PlaySound("newWave", false, 1000);
	}

	if (input->MouseBtnJustDown(0) && placingTower_ != nullptr && !input->InputCaught())
	{
		Vec2 pos = input->MousePos() + world->camPos;
		int cost = tManager_->GetCost(placingTowerName_);
		if (map_->CanPlace(pos) && plMoney >= cost && tManager_->GetColliding(placingTower_->GetHitbox()) == nullptr)
		{
			tManager_->NewTower(placingTowerName_, pos);
			placingTowerName_ = "";
			placingTower_ = nullptr;
			plMoney -= cost;
		}
	}

	if (towerMenuBtn->justPressed_)
	{
		for (int i = 0; i < (int)towerBtns.size(); i++)
		{
			towerBtns[i]->visible_ = !towerBtns[i]->visible_;
		}
	}

	for (int i = 0; i < (int)towerBtns.size(); i++)
	{
		if (towerBtns[i]->justPressed_)
		{
			placingTowerName_ = tManager_->towerTypes_[i];
			if (placingTower_ != nullptr)
				delete placingTower_;
			placingTower_ = new Entity();
			placingTower_->SetAnimID(towerAnim);
			placingTower_->SetOffset(Vec2(-16.f, -24.f));
			placingTower_->SetHitbox(-16, -24, 32, 48);
			placingTower_->SetTextureID("tower_" + placingTowerName_);
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
	if (input->KeyJustDown('4'))
	{
		world->ChangeSpeedMult(8.f);
	}
	if (input->KeyJustDown(' '))
	{
		world->ToggleFixedStep();
	}

	if (placingTower_ != nullptr)
		placingTower_->SetPosition(input->MousePos() + world->camPos);

	//replace 2048 with mapWidth, 1600 with scrWidth at some point
	//same with heights
	if (world->camPos.x_ < 0)
		world->camPos.x_ = 0;
	if (world->camPos.x_ > 2048.f - gfx->GetWidth())
		world->camPos.x_ = 2048.f - gfx->GetWidth();
	if (world->camPos.y_ < 0)
		world->camPos.y_ = 0;
	if (world->camPos.y_ > 1024.f - gfx->GetHeight())
		world->camPos.y_ = 1024.f - gfx->GetHeight();

	tManager_->Update(delta);
	if (!spawning_)
		cManager_->Update(delta);
	pManager_->Update(delta);

	lastSpawning_ = spawning_;
}

void GameScene::FixedUpdate()
{
	if (!spawning_)
		cManager_->FixedUpdate();
	tManager_->FixedUpdate();
	pManager_->FixedUpdate();
	Scene::FixedUpdate();

	if (placingTower_ != nullptr)
		placingTower_->FixedUpdate();

	if (cManager_->AllDead())
	{
		StartSpawning();
		//cManager_->spawnDelay_ *= 0.9f;
	}

	if (plHealth <= 0)
	{
		plHealth = 0;
		world->SetActiveScene("GameOverScene");
	}
}

void GameScene::Draw(float interp)
{		
	map_->Draw(interp);
	cManager_->Draw(interp);
	tManager_->Draw(interp);
	pManager_->Draw(interp);

	if (placingTower_ != nullptr)
		placingTower_->Draw(interp);

	gfx->BlitText(Vec2(10, 10), "Money: " + std::to_string(plMoney), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 35), "Health: " + std::to_string(plHealth), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 60), "Wave: " + std::to_string(wave), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 85), "Creeps left: " + std::to_string(numCreeps), Colour(0, 0, 0));
	Scene::Draw(interp);
}