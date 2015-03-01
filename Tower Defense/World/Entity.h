#pragma once

#include <string>

#include <World/World.h>
#include <Math/Vec2.h>
#include <Math/Rect.h>

class Scene;

class Entity
{
protected:	
	Vec2 lastPosition_;
	Vec2 position_;
	Vec2 offset_;
	Rect hitbox_;
	Vec2 hitboxOffset_;

	std::string textureID_ = "";
	int animID_ = -1;

	std::string tag_ = "";

public:			
	float rotation = 0.0f;
	bool drawhb = false;
	Entity(const Vec2& position = Vec2(0.f, 0.f), const std::string& textureID = "");
	virtual ~Entity();

	void SetAnimID(int animID) { animID_ = animID; }
	void SetTextureID(std::string texID){ textureID_ = texID; }

	void SetTag(std::string tag){ tag_ = tag; }
	std::string GetTag(){ return tag_; }

	void SetHitbox(int x, int y, int width, int height);
	Rect& GetHitbox();

	void SetOffset(const Vec2& offset){ offset_ = offset; }
	void SetPosition(const Vec2& position){ position_ = position; lastPosition_ = position; }
	Vec2 GetPosition() const { return position_; }	

	virtual void Update(float delta){};
	virtual void FixedUpdate();
	virtual void Draw(float interp);
};

