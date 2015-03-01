#pragma once
#include <World/Scene.h>
#include <UI/Button.h>
#include <Game/Map.h>
#include <Audio.h>

class MenuScene : public Scene
{
private:
	Map* map = nullptr;

	Button* playBtn = nullptr;
	Button* exitBtn = nullptr;

	Button* map1Btn = nullptr;
	Button* map2Btn = nullptr;
	Button* map3Btn = nullptr;

	std::string mapChoice_ = "";

public:
	MenuScene();

	void Update(float delta) override;

	void SwitchedTo(const std::string& from) override;
	void SwitchedFrom(const std::string& to) override;
};
