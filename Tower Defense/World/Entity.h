#pragma once

#include <string>

#include <World/World.h>
#include <Math/Vec2.h>

class Scene;

class Entity
{
protected:	
	Vec2 position_;
	Vec2 offset_;

	std::string textureID_ = "";
	int animID_ = -1;

	std::string tag_ = "";

	Scene* scene_ = nullptr;

public:			
	float rotation = 0.0f;

	Entity(Scene* scene, const Vec2& position = Vec2(0.f, 0.f), const std::string& textureID = "");
	virtual ~Entity();

	void SetAnimID(int animID) { animID_ = animID; }
	void SetTextureID(std::string texID){ textureID_ = texID; }

	void SetTag(std::string tag){ tag_ = tag; }
	std::string GetTag(){ return tag_; }

	void SetOffset(const Vec2& offset){ offset_ = offset; }
	void SetPosition(const Vec2& position){ position_ = position; }
	Vec2 GetPosition() const { return position_; }	

	virtual void Update(float delta);
	virtual void FixedUpdate(){};
	virtual void Draw();
};

