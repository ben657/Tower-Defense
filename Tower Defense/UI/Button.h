#pragma once

#include <UI/UIComponent.h>
#include <Input.h>
#include <Math/Math.h>

class Button : public UIComponent
{
private:
	Rect rect_;
	std::string text_ = "";
	Colour colour_;	
	Colour highLightCol_;
	bool pressed_ = false;
	
public:
	Vec2 iconOffset_;

	bool justPressed_ = false;
	bool visible_ = true;

	Button(Rect rect, std::string text, Colour colour);
	~Button();

	void Update(float delta) override;
	void Draw(float interp) override;
};

