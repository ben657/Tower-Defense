#pragma once

#include <map>
#include <string>
#include <time.h>

#include <Math/Vec2.h>
#include <Graphics/Graphics.h>

class Scene;

class World
{
private:
	static World* instance_;

	std::map<std::string, Scene*> scenes_;
	std::string activeID_ = "";
	Scene* activeScene_ = nullptr;
	float lastFrameTime_ = 0;
	float frameTime_ = 0;
	float delta_ = 1000.f / 60.f;
	float baseDelta_ = 1000.f / 60.f;
	bool doFixedStep_ = true;

	int score_ = 0;
	std::string level_ = "";

protected:
	World();

public:	
	Vec2 camPos;

	static World* Instance();
	~World();

	void Initialise(int width, int height);
	void Start();

	void ChangeSpeedMult(float mult){ delta_ = baseDelta_ / mult; }
	float GetFDelta(){ return baseDelta_; }

	int GetScore(){ return score_; }
	void SetScore(int score){ score_ = score; }

	std::string GetLevel(){ return level_; }
	void SetLevel(const std::string& level){ level_ = level; }

	void AddScene(Scene* scene, const std::string& uid);
	Scene* GetScene(const std::string& uid);
	void SetActiveScene(const std::string& uid);
	Scene* GetActiveScene();

	void ToggleFixedStep(){ doFixedStep_ = !doFixedStep_; }
	bool FixedStepRunning() { return doFixedStep_; }

	void Draw(float interp);
};

#define world World::Instance()

