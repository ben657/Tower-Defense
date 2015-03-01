#include "Button.h"

Button::Button(Rect rect, std::string text, Colour colour) : rect_(rect), text_(text), colour_(colour)
{
	highLightCol_ = colour_;
	highLightCol_.r = math::max(0, (int)highLightCol_.r - 30);
	highLightCol_.g = math::max(0, (int)highLightCol_.g - 30);
	highLightCol_.b = math::max(0, (int)highLightCol_.b - 30);
}

void Button::SetColour(const Colour& colour)
{
	colour_ = colour;
	highLightCol_ = colour_;
	highLightCol_.r = math::max(0, (int)highLightCol_.r - 30);
	highLightCol_.g = math::max(0, (int)highLightCol_.g - 30);
	highLightCol_.b = math::max(0, (int)highLightCol_.b - 30);
}

void Button::Update(float delta)
{
	justPressed_ = false;

	if (!visible_)
		return;
	
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
	if (pressed_)
	{
		input->SetInputCaught(true);
	}
}

void Button::Draw(float interp)
{
	if (!visible_)
		return;

	gfx->BlitRect(rect_, pressed_ ? highLightCol_ : colour_);
	if (textureID_ != "")
	{
		Vec2 pos((float)rect_.left_, (float)rect_.top_);
		pos += iconOffset_;
		gfx->BlitAlpha(pos, textureID_);
	}
}