#pragma once

#include <World\Scene.h>

class Map : public Entity
{
private:
	std::string name_ = "";

public:
	Map(Scene* scene, const std::string& name);

	bool CanPlace(const Vec2& position);

	void Draw() override;
};

