#pragma once
#include <World/Scene.h>
#include <UI/Button.h>
#include <Game/Map.h>

class MenuScene : public Scene
{
private:
	Map* map = nullptr;

	Button* playBtn = nullptr;
	Button* optionsBtn = nullptr;
	Button* exitBtn = nullptr;

public:
	MenuScene();
	~MenuScene();

	void Update(float delta) override;

	void* SwitchedFrom(const std::string& to) override;
};

