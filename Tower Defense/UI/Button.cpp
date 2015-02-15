#include "Button.h"

Button::Button(Rect rect, std::string text, Colour colour) : rect_(rect), text_(text), colour_(colour)
{
	highLightCol_ = colour_;
	highLightCol_.r = math::min(255, (int)highLightCol_.r - 25);
	highLightCol_.g = math::min(255, (int)highLightCol_.g - 25);
	highLightCol_.b = math::min(255, (int)highLightCol_.b - 25);
}

Button::~Button()
{

}

void Button::Update(float delta)
{
	if (!visible_)
		return;

	justPressed_ = false;
	if (input->MouseBtnJustDown(0))
	{
		Vec2 mPos = input->MousePos();
		if (rect_.Contains(mPos))
		{
			pressed_ = true;
		}
	}
	if (input->MouseBtnJustUp(0) && pressed_)
	{
		Vec2 mPos = input->MousePos();
		if (rect_.Contains(mPos))
		{			
			justPressed_ = true;
		}
		pressed_ = false;
	}
}

void Button::Draw()
{
	if (!visible_)
		return;

	gfx->BlitRect(rect_, pressed_ ? highLightCol_ : colour_);
	if (textureID_ != "")
	{
		Vec2 pos(rect_.left_, rect_.top_);
		pos += iconOffset_;
		gfx->BlitAlpha(pos, textureID_);
	}
}