#pragma once

#include <World/Scene.h>

class Creep : public Entity
{
protected:
	int path_ = 0;
	int pathIndex_ = 0;
	Vec2 pathPoint_;

	int health_ = 0;
	int damage_ = 0;
	float speed_ = 0.0f;

public:
	Creep(int x, int y, const std::string& textureID, int path) : Entity(x, y, textureID), path_(path){};
	~Creep();

	virtual void Update(float delta) override;
	void FixedUpdate() override;
};