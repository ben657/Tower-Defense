#pragma once

#include <HAPI_lib.h>
#include <map>
#include <unordered_map>
#include <Math/Vec2.h>

struct Colour
{		
	BYTE b = 0;
	BYTE g = 0;
	BYTE r = 0;
	BYTE a = 1;

	Colour(BYTE red = 0, BYTE green = 0, BYTE blue = 0, BYTE alpha = 0) : r(red), b(blue), g(green), a(alpha)
	{}
};

class Texture;
class Animation;
class Rect;

class Graphics
{
private:
	static Graphics* instance_;

	BYTE* screenPtr_;
	int scrWidth_ = 0;
	int scrHeight_ = 0;
	Colour clearColour_;

	std::unordered_map<std::string, Texture*> textures_;
	std::vector<Animation*> animations_;

protected:
	Graphics();

public:	
	static Graphics* Instance();
 
	~Graphics();	

	void Initialise(int screenWidth, int screenHeight);
	
	int GetScreenWidth(){ return scrWidth_; }
	int GetScreenHeight(){ return scrHeight_; }

	void SetClearColour(float r, float g, float b);
	void Clear();

	void LoadTexture(std::string loadPath, std::string uid);
	void CreateTexture(Colour& colour, int width, int height, std::string uid);

	int CreateAnimation(int startFrame, int endFrame, int frameWidth, int frameHeight, int framesAcross, int framesDown, int fps);
	void UpdateAnimation(const int animID, float delta);

	Colour PixelAt(const Vec2& position);
	Colour PixelAt(const Vec2& position, const std::string uid);

	void Blit(const Vec2& position, const std::string& uid, int width, int height);
	void Blit(const Vec2& position, const std::string& uid, const float angle);
	void BlitRect(const Vec2& position, int width, int height, const Colour& colour);
	void BlitAlpha(const Vec2& position, const std::string& uid);
	void BlitAnimated(const Vec2& position, const std::string& texID, const int animID);

	void BlitLine(const Vec2& p1, const Vec2& p2, const Colour& colour);
};

#define gfx Graphics::Instance()

