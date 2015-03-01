#pragma once

#include <World/Scene.h>
#include <UI/Button.h>
#include <fstream>
#include <algorithm>

struct Score
{
	std::string name = "";
	int score = 0;
};

class GameOverScene : public Scene
{
private:
	Button* tryAgainBtn_ = nullptr;
	Button* mainMenuBtn_ = nullptr;
	Button* inputDoneBtn_ = nullptr;

	std::string mapName_;
	int score_ = 0;
	bool takingInput_ = true;
	std::string input_ = "_ _ _";
	int currentInput_ = 0;

	std::vector<Score> scores_;

public:
	GameOverScene();
	~GameOverScene();

	void SwitchedTo(const std::string& from);
	void SwitchedFrom(const std::string& to);

	void Update(float delta) override;
	void Draw(float interp) override;
};

