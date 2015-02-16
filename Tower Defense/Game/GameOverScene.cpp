#include "GameOverScene.h"


GameOverScene::GameOverScene()
{
	gfx->LoadTexture("Data/buttons/tryAgain.png", "btn_tryAgain");
	gfx->LoadTexture("Data/buttons/mainMenu.png", "btn_mainMenu");

	tryAgainBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, 4 * gfx->GetHeight() / 6, 270, 76), "", Colour(104, 72, 51));
	tryAgainBtn->iconOffset_ = Vec2(7.f, 5.f);
	tryAgainBtn->SetTextureID("btn_tryAgain");
	AddEntity(tryAgainBtn);

	mainMenuBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, 5 * gfx->GetHeight() / 6, 270, 76), "", Colour(104, 72, 51));
	mainMenuBtn->iconOffset_ = Vec2(7.f, 5.f);
	mainMenuBtn->SetTextureID("btn_mainMenu");
	AddEntity(mainMenuBtn);
}

GameOverScene::~GameOverScene()
{
}

void GameOverScene::SwitchedTo(const std::string& from, void* data)
{
	mapName = (char*)data;
}

void* GameOverScene::SwitchedFrom(const std::string& to)
{
	if (to == "GameScene")
		return (void*)mapName;
	return nullptr;
}

void GameOverScene::Update(float delta)
{
	Scene::Update(delta);

	if (tryAgainBtn->justPressed_)
		world->SetActiveScene("GameScene");

	if (mainMenuBtn->justPressed_)
		world->SetActiveScene("MenuScene");
}
