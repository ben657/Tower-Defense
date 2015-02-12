#include "GameScene.h"

GameScene::GameScene(const std::string& mapName)
{
	srand(time(0));

	HAPI->SetShowFPS(true);

	cManager_ = new CreepManager(this, 1000);
	pManager_ = new ProjectileManager(this, 100);
	tManager_ = new TowerManager(this, 100);	

	map = new Map((Scene*)this, mapName);
	AddEntity(map);

	cManager_->LoadCreepData("bunny");
	cManager_->LoadCreepData("unicorn");

	tManager_->LoadTowerData("fireBall");

	gfx->LoadTexture("Data/projectiles/fireBall.png", "proj_fireBall");

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

	SpawnWave();
}

GameScene::~GameScene()
{

}

bool GameScene::PlaceTurret(const Vec2& position)
{
	if (!map->CanPlace(position))
		return false;

	//Make turret
	return true;
}

void GameScene::SpawnWave()
{
	wave++;
	int maxDifficulty = wave * 50;
	int waveDifficulty = 0;
	while (waveDifficulty < maxDifficulty)
	{
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
		world->ChangeSpeedMult(10.f);
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

	if (input->MouseBtnJustDown(0))
	{
		if (map->CanPlace(input->MousePos()))
		{
			if (plMoney >= tManager_->GetCost("fireBall"))
			{
				tManager_->NewTower("fireBall", input->MousePos());
				plMoney -= tManager_->GetCost("fireBall");
			}
		}
	}	

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
	Scene::Draw();
	cManager_->Draw();
	tManager_->Draw();
	pManager_->Draw();
	gfx->BlitText(Vec2(10, 10), "Money: " + std::to_string(plMoney), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 35), "Health: " + std::to_string(plHealth), Colour(0, 0, 0));
	gfx->BlitText(Vec2(10, 50), "Wave: " + std::to_string(wave), Colour(0, 0, 0));
}