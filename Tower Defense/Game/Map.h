#pragma once

#include <World\Scene.h>

class Map : public Entity
{
private:
	

public:
	std::string name_ = "";

	Map(Scene* scene, const std::string& name);

	bool CanPlace(const Vec2& position);

	void Update(float delta) override{};
	void Draw() override;
};