#pragma once

#include <HAPI_lib.h>
#include <Math/Vec2.h>

class Input
{
private:
	static Input* instance_;

	HAPI_TKeyboardData* kData = nullptr;
	HAPI_TKeyboardData* lastKD = nullptr;

	HAPI_TMouseData* mData = nullptr;
	HAPI_TMouseData* lastMD = nullptr;

	HAPI_TControllerData** cData = nullptr;
	bool* controllers = nullptr;

protected:
	Input();

public:
	static Input* Instance();

	~Input();

	void Initialise();

	bool KeyDown(const int key);
	bool KeyJustDown(const int key);
	bool KeyJustUp(const int key);

	bool MouseBtnDown(const int btn);
	bool MouseBtnJustDown(const int btn);
	bool MouseBtnJustUp(const int btn);
	Vec2 MousePos(){ return Vec2((float)mData->x, (float)mData->y); }
	Vec2 MouseDelta(){ return Vec2((float)mData->x, (float)mData->y) - Vec2((float)lastMD->x, (float)lastMD->y); }

	void Update();
};

#define input Input::Instance()
