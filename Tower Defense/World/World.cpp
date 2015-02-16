#include <World/World.h>

#include <World/Scene.h>
#include <Input.h>

World* World::instance_ = nullptr;

World* World::Instance()
{
	if (instance_ == nullptr)
		instance_ = new World();

	return instance_;
}

World::World()
{
}

World::~World()
{
	for (auto iterator : scenes_)
	{
		delete iterator.second;
	}
}

void World::Initialise(int width, int height)
{	
	gfx->Initialise(width, height);
	gfx->SetClearColour(0.f, 0.f, 0.f);

	input->Initialise();

	HAPI->ChangeFont("Arial", 16, 20);

	lastFrameTime_ = (float)HAPI->GetTime();
}

void World::Start()
{
	HAPI->SetShowFPS(true);
	float sinceUpdate = 0.0f;

	while (HAPI->Update())
	{
		frameTime_ = (float)HAPI->GetTime() - lastFrameTime_;
		lastFrameTime_ = (float)HAPI->GetTime();

		sinceUpdate += frameTime_;

		if (sinceUpdate > delta_ && doFixedStep_)
		{					
			activeScene_->FixedUpdate();
			sinceUpdate = 0.0f;	
		}	
		if (!doFixedStep_){ sinceUpdate = 0; }

		input->Update();
		activeScene_->Update(frameTime_);
		Draw(sinceUpdate / delta_);
	}
}

void World::AddScene(Scene* scene, std::string uid)
{
	scenes_[uid] = scene;
}

Scene* World::GetScene(std::string uid)
{
	if (scenes_.find(uid) == scenes_.end())
		return nullptr;
	return scenes_[uid];
}

void World::SetActiveScene(std::string uid)
{
	void* data = nullptr;
	if (activeScene_ != nullptr)
		data = activeScene_->SwitchedFrom(uid);

	activeScene_ = scenes_[uid];
	activeScene_->SwitchedTo(activeID_, data);
	activeID_ = uid;
}

Scene* World::GetActiveScene()
{
	return activeScene_;
}

void World::Draw(float interp)
{
	HAPI->DebugText(std::to_string(interp));
	gfx->Clear();
	activeScene_->Draw(interp);	
}
