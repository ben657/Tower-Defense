#include "GameScene.h"

GameScene::GameScene()
{
	HAPI->SetShowFPS(true);

	cManager_ = new CreepManager(this, 100);
	pManager_ = new ProjectileManager(100);
	tManager_ = new TowerManager(this, 100);	

	map = new Map((Scene*)this, "map1");
	AddEntity(map);

	gfx->LoadTexture("Data/creeps/bunny.png", "creep_bunny");
	gfx->LoadTexture("Data/towers/fireBall.png", "tower_fireBall");
	gfx->LoadTexture("Data/projectiles/fireBall.png", "proj_fireBall");

	pathLengths_ = new int[2];
	pathLengths_[0] = 11;
	pathLengths_[1] = 3;

	paths_.resize(2);
	std::ifstream pathFile;
	pathFile.open("Data/maps/map1/paths.txt");

	for (int i = 0; i < pathLengths_[0]; i++)
	{
		int x = 0;
		int y = 0;
		pathFile >> x;
		pathFile >> y;
		paths_[0].push_back(Vec2((float)x, (float)y));
	}
	float test = paths_[0][0].x_;

	pathFile.close();

	cManager_->NewCreep("bunny", 0);
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

Vec2 GameScene::NextPoint(int path, int currentIndex)
{
	if (currentIndex + 1 >= pathLengths_[path])
		return paths_[path][pathLengths_[path] - 1];
	return paths_[path][currentIndex + 1];
}

void GameScene::Update(float delta)
{
	Scene::Update(delta);	

	if (input->MouseBtnJustDown(0))
	{
		if (map->CanPlace(input->MousePos()))
		{
			tManager_->NewTower("fireBall", input->MousePos());
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
}

void GameScene::Draw()
{	
	Scene::Draw();
	cManager_->Draw();
	tManager_->Draw();
	pManager_->Draw();
}