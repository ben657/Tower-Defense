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
	float spareTime = 0.0f;
	while (HAPI->Update())
	{
		frameTime_ = (float)HAPI->GetTime() - lastFrameTime_;
		lastFrameTime_ = (float)HAPI->GetTime();

		spareTime += frameTime_;

		while (spareTime >= 0.f && doFixedStep_)
		{
			activeScene_->FixedUpdate();
			spareTime -= delta_;
		}
		if (!doFixedStep_){ spareTime = 0; }

		input->Update();
		activeScene_->Update(frameTime_);
		float interp = (delta_ + spareTime) / delta_;
		Draw(interp);
	}
}

void World::AddScene(Scene* scene, const std::string& uid)
{
	scenes_[uid] = scene;
}

Scene* World::GetScene(const std::string& uid)
{
	if (scenes_.find(uid) == scenes_.end())
		return nullptr;
	return scenes_[uid];
}

void World::SetActiveScene(const std::string& uid)
{
	if (activeScene_ != nullptr)
		activeScene_->SwitchedFrom(uid);

	activeScene_ = scenes_[uid];
	activeScene_->SwitchedTo(activeID_);
	activeID_ = uid;
}

Scene* World::GetActiveScene()
{
	return activeScene_;
}

void World::Draw(float interp)
{
	gfx->Clear();
	activeScene_->Draw(interp);	
}
