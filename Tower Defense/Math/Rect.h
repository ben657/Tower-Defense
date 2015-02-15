#pragma once

#include <Math/Vec2.h>

class Rect
{
public:

	int left_ = 0;	
	int right_ = 0;
	int top_ = 0;
	int bottom_ = 0;

	Rect(int left = 0, int top = 0, int width = 0, int height = 0);
	~Rect();

	bool Intersects(const Rect& other) const;
	bool Contains(const Vec2& point) const;
	void ClipTo(const Rect& other);
	void MoveTo(int x, int y);
	int Width() const;
	int Height() const;
};

