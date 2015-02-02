#pragma once

#include <Game/Creep.h>
#include <vector>
#include <map>

class GameScene;

struct CreepData
{
	int health = 0;
	int attack = 0;
	float speed = 0.f;
	Vec2 offset;
	int idleAnim = -1;
	int moveAnim = -1;
	int attackAnim = -1;
};

class CreepManager
{
private:
	GameScene* scene_ = nullptr;

	std::map<std::string, CreepData> creepDatas_;
	std::vector<Creep*> creeps_;

	Creep* GetFirstInactive();

public:
	CreepManager(GameScene* scene, int initialNum);
	~CreepManager();

	void NewCreep(const std::string& type, int path);

	void Update(float delta);
	void FixedUpdate();
	void Draw();
};

