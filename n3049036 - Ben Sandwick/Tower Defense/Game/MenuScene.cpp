#include "MenuScene.h"


MenuScene::MenuScene()
{
	gfx->LoadTexture("Data/buttons/play.png", "btn_play");
	gfx->LoadTexture("Data/buttons/options.png", "btn_options");
	gfx->LoadTexture("Data/buttons/exit.png", "btn_exit");

	gfx->LoadTexture("Data/buttons/map1btn.png", "btn_map1");
	gfx->LoadTexture("Data/buttons/map2btn.png", "btn_map2");
	gfx->LoadTexture("Data/buttons/map3btn.png", "btn_map3");

	audio->LoadSound("Data/sounds/menuLoop.wav", "menuLoop");

	map = new Map(this, "map1");
	AddEntity(map);

	playBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	playBtn->iconOffset_ = Vec2(7.f, 5.f);
	playBtn->SetTextureID("btn_play");
	AddEntity(playBtn);

	exitBtn = new Button(Rect(gfx->GetWidth() / 2 - 135, 4 * gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	exitBtn->iconOffset_ = Vec2(7.f, 5.f);
	exitBtn->SetTextureID("btn_exit");
	AddEntity(exitBtn);

	map1Btn = new Button(Rect(gfx->GetWidth() / 4 - 135, 2 * gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	map1Btn->iconOffset_ = Vec2(7.f, 5.f);
	map1Btn->SetTextureID("btn_map1");
	AddEntity(map1Btn);

	map2Btn = new Button(Rect((2 * gfx->GetWidth()) / 4 - 135, 2 * gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	map2Btn->iconOffset_ = Vec2(7.f, 5.f);
	map2Btn->SetTextureID("btn_map2");
	AddEntity(map2Btn);

	map3Btn = new Button(Rect((3 * gfx->GetWidth()) / 4 - 135, 2 * gfx->GetHeight() / 5, 270, 76), "", Colour(104, 72, 51));
	map3Btn->iconOffset_ = Vec2(7.f, 5.f);
	map3Btn->SetTextureID("btn_map3");
	AddEntity(map3Btn);
}

void MenuScene::SwitchedTo(const std::string& from)
{
	audio->PlaySound("menuLoop", true, 1000);
}

void MenuScene::SwitchedFrom(const std::string& to)
{
	audio->StopSound("menuLoop");

	//world->SetLevel("helix");
}

void MenuScene::Update(float delta)
{
	Scene::Update(delta);

	if (playBtn->justPressed_ && mapChoice_ != "")
	{
		world->SetLevel(mapChoice_);
		world->SetActiveScene("GameScene");
	}

	if (exitBtn->justPressed_)
		HAPI->Close();

	if (map1Btn->justPressed_)
	{
		map1Btn->SetColour(Colour(255, 0, 0));
		map2Btn->SetColour(Colour(104, 72, 51));
		map3Btn->SetColour(Colour(104, 72, 51));
		mapChoice_ = "Helix";
	}

	if (map2Btn->justPressed_)
	{
		map2Btn->SetColour(Colour(255, 0, 0));
		map1Btn->SetColour(Colour(104, 72, 51));
		map3Btn->SetColour(Colour(104, 72, 51));
		mapChoice_ = "Heat Stroke";
	}

	if (map3Btn->justPressed_)
	{
		map3Btn->SetColour(Colour(255, 0, 0));
		map1Btn->SetColour(Colour(104, 72, 51));
		map2Btn->SetColour(Colour(104, 72, 51));
		mapChoice_ = "Snowed In";
	}
}
