#include "GameOverScene.h"

GameOverScene::GameOverScene()
{
	gfx->LoadTexture("Data/buttons/tryAgain.png", "btn_tryAgain");
	gfx->LoadTexture("Data/buttons/mainMenu.png", "btn_mainMenu");
	gfx->LoadTexture("Data/buttons/done.png", "btn_done");

	tryAgainBtn_ = new Button(Rect(gfx->GetWidth() / 2 - 135, 4 * gfx->GetHeight() / 6, 270, 76), "", Colour(104, 72, 51));
	tryAgainBtn_->iconOffset_ = Vec2(7.f, 5.f);
	tryAgainBtn_->SetTextureID("btn_tryAgain");
	AddEntity(tryAgainBtn_);

	mainMenuBtn_ = new Button(Rect(gfx->GetWidth() / 2 - 135, 5 * gfx->GetHeight() / 6, 270, 76), "", Colour(104, 72, 51));
	mainMenuBtn_->iconOffset_ = Vec2(7.f, 5.f);
	mainMenuBtn_->SetTextureID("btn_mainMenu");
	AddEntity(mainMenuBtn_);

	inputDoneBtn_ = new Button(Rect(gfx->GetWidth() / 2 - 135, 4 * gfx->GetHeight() / 6, 270, 76), "", Colour(104, 72, 51));
	inputDoneBtn_->iconOffset_ = Vec2(7.f, 5.f);
	inputDoneBtn_->SetTextureID("btn_done");
	AddEntity(inputDoneBtn_);

	tryAgainBtn_->visible_ = false;
	mainMenuBtn_->visible_ = false;
	inputDoneBtn_->visible_ = true;
}

GameOverScene::~GameOverScene()
{
	Scene::~Scene();
}

void GameOverScene::SwitchedTo(const std::string& from, void* data)
{
	HAPI->ChangeFont("Arial", 42, 700);

	mapName_ = (char*)data;
	score_ = world->GetScore();
}

void* GameOverScene::SwitchedFrom(const std::string& to)
{
	if (to == "GameScene")
		return (void*)mapName_;

	std::ofstream file;
	file.open("Data/highScores.txt");

	for (int i = 0; i < (int)scores_.size(); i++)
	{
		Score s = scores_[i];
		std::string line = s.name + " " + std::to_string(s.score) + "\n";
		file.write(line.c_str(), line.length());
	}

	file.close();

	return nullptr;
}

void GameOverScene::Update(float delta)
{
	Scene::Update(delta);

	if (takingInput_)
	{
		if (currentInput_ <= 4)
		{
			for (int i = 65; i < 91; i++)
			{
				if (input->KeyJustDown(i))
				{
					input_[currentInput_] = (char)i;
					currentInput_ += 2;
				}
			}
		}

		if (inputDoneBtn_->justPressed_)
		{
			takingInput_ = false;
			tryAgainBtn_->visible_ = true;
			mainMenuBtn_->visible_ = true;
			inputDoneBtn_->visible_ = false;

			std::ifstream hsFile;
			hsFile.open("Data/highScores.txt");
			int numEntries = 10;
			int i = 0;
			bool addedPlayer_ = false;
			for (; i < numEntries && !hsFile.eof(); i++)
			{
				Score s;

				hsFile >> s.name;
				hsFile >> s.score;

				if (score_ > s.score)
				{
					input_.erase(std::remove(input_.begin(), input_.end(), ' '), input_.end());
					Score ps;
					ps.name = input_;
					ps.score = score_;
					scores_.push_back(ps);
					i++;
					addedPlayer_ = true;
				}				

				scores_.push_back(s);				
			}

			if (!addedPlayer_ && i < 10)
			{
				input_.erase(std::remove(input_.begin(), input_.end(), ' '), input_.end());
				Score s;
				s.name = input_;
				s.score = score_;
				scores_.push_back(s);
				i++;
				addedPlayer_ = true;
			}

			hsFile.close();
		}

		return;
	}

	if (tryAgainBtn_->justPressed_)
		world->SetActiveScene("GameScene");

	if (mainMenuBtn_->justPressed_)
		world->SetActiveScene("MenuScene");
}

void GameOverScene::Draw(float interp)
{
	Scene::Draw(interp);

	int xmid = (int)(gfx->GetWidth() * 0.5f);
	int ymid = (int)(gfx->GetHeight() * 0.5f);

	if (takingInput_)
	{		
		HAPI->RenderText(xmid - 180, ymid - 50, HAPI_TColour(255, 255, 255), "You survived " + std::to_string(score_) + " waves!");
		HAPI->RenderText(xmid - 50, ymid, HAPI_TColour(255, 255, 255), input_);
	}
	else
	{
		int yStart = ymid - gfx->GetHeight() / 5;
		int x = xmid - 120;
		for (int i = 0; i < (int)scores_.size(); i++)
		{
			std::string text = std::to_string(i + 1) + ". " + scores_[i].name + " - " + std::to_string(scores_[i].score);
			HAPI->RenderText(x, yStart + 50 * i, HAPI_TColour(255, 255, 255), text);
		}
	}
}
