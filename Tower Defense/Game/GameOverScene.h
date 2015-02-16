#pragma once

#include <World/Scene.h>
#include <UI/Button.h>

class GameOverScene : public Scene
{
private:
	Button* tryAgainBtn = nullptr;
	Button* mainMenuBtn = nullptr;

	char* mapName = nullptr;

public:
	GameOverScene();
	~GameOverScene();

	void SwitchedTo(const std::string& from, void* data);
	void* SwitchedFrom(const std::string& to);

	void Update(float delta) override;
};

