#include "Rect.h"


Rect::Rect(int left, int top, int width, int height) : left_(left), top_(top), right_(left + width), bottom_(top + height)
{
}


Rect::~Rect()
{
}

bool Rect::Contains(const Vec2& point) const
{
	return (point.x_ > left_ && point.x_ < right_ && point.y_ > top_ && point.y_ < bottom_);
}

bool Rect::Intersects(const Rect& other) const
{
	return (left_ < other.right_ && right_ > other.left_ && top_ < other.bottom_ && bottom_ > other.top_);
}

void Rect::ClipTo(const Rect& other)
{
	if (left_ < other.left_)
		left_ = other.left_;

	if (right_ > other.right_)
		right_ = other.right_;

	if (top_ < other.top_)
		top_ = other.top_;

	if (bottom_ > other.bottom_)
		bottom_ = other.bottom_;
}

void Rect::MoveTo(int x, int y)
{
	int xDiff = x - left_;
	int yDiff = y - top_;
	left_ += xDiff;
	top_ += yDiff;
	right_ += xDiff;
	bottom_ += yDiff;
}

int Rect::Width() const
{
	return right_ - left_;
}

int Rect::Height() const
{
	return bottom_ - top_;
}
