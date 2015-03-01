#include <HAPI_lib.h>
#include <World/World.h>
#include <Graphics/Graphics.h>
#include <Input.h>
//#include <vld.h>
#include <Game/MenuScene.h>
#include <Game/GameScene.h>
#include <Game/GameOverScene.h>

void HAPI_Main()
{
	world->Initialise(1366, 768);
	MenuScene* menuScene = new MenuScene();
	GameScene* gameScene = new GameScene();	
	GameOverScene* gameOverScene = new GameOverScene();
	
	world->AddScene(menuScene, "MenuScene");
	world->AddScene(gameScene, "GameScene");
	world->AddScene(gameOverScene, "GameOverScene");
	world->SetActiveScene("MenuScene");
	world->Start();
	
	delete world;
	delete gfx;
	delete input;
	delete audio;
}