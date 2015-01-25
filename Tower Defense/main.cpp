#include <HAPI_lib.h>
#include <World/World.h>
#include <Graphics/Graphics.h>
#include <Input.h>

#include <Game/GameScene.h>

void HAPI_Main()
{
	world->Initialise(1600, 900);

	GameScene* gameScene = new GameScene();

	world->AddScene(gameScene, "GameScene");
	world->SetActiveScene("GameScene");
	world->Start();
	
	delete world;
	delete gfx;
	delete input;
}