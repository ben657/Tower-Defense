#include "MenuScene.h"


MenuScene::MenuScene()
{
	gfx->LoadTexture("Data/buttons/play.png", "btn_play");
	gfx->LoadTexture("Data/buttons/options.png", "btn_options");
	gfx->LoadTexture("Data/buttons/exit.png", "btn_exit");

	map = new Map(this, "map1");
	AddEntity(map);

	playBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	playBtn->iconOffset_ = Vec2(7.f, 5.f);
	playBtn->SetTextureID("btn_play");
	AddEntity(playBtn);

	optionsBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, 2 * gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	optionsBtn->iconOffset_ = Vec2(7.f, 5.f);
	optionsBtn->SetTextureID("btn_options");
	AddEntity(optionsBtn);

	exitBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, 4 * gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	exitBtn->iconOffset_ = Vec2(7.f, 5.f);
	exitBtn->SetTextureID("btn_exit");
	AddEntity(exitBtn);
}

MenuScene::~MenuScene()
{

}

void* MenuScene::SwitchedFrom(const std::string& to)
{
	char* map = "map2";
	return map;
}

void MenuScene::Update(float delta)
{
	Scene::Update(delta);

	if (playBtn->justPressed_)
		world->SetActiveScene("GameScene");

	if (exitBtn->justPressed_)
		HAPI->Close();
}
