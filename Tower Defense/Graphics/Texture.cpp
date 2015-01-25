#include "Texture.h"
#include <iostream>
Texture::Texture(int width, int height) : width_(width), height_(height)
{
	data_ = new BYTE[width * height * 4];
}

Texture::Texture(std::string loadPath)
{
	LoadFromFile(loadPath);
}

Texture::~Texture()
{
//	if (data_ != nullptr)
		delete[] data_;
}

bool Texture::LoadFromFile(std::string loadPath)
{
	HAPI->LoadTexture(loadPath, &data_, &width_, &height_);
	return true;
}

void Texture::Fill(const Colour& colour)
{
	for (int i = 0; i < width_ * height_ * 4; i += 4)
	{
		memcpy(data_ + i, &colour, 4);
	}
}

Colour Texture::PixelAt(const Vec2& position)
{
	BYTE* offset = data_ + ((int)position.x_ + (int)position.y_ * width_) * 4;
	return Colour((int)offset[3], (int)offset[2], (int)offset[1], (int)offset[0]);
}

void Texture::Blit(const Vec2& position, BYTE* screenPtr, const Rect& screenRect, int width, int height)
{
	BYTE* screenOffset = screenPtr;

	int texByteWidth = width_ << 2;

	int aWidth = width > 0 ? width : width_;
	int aHeight = height > 0 ? height : height_;

	for (int tY = 0; tY < aHeight; tY++)
	{
		memcpy(screenOffset, data_ + texByteWidth * tY, texByteWidth);
		screenOffset += aWidth * 4;
	}
}

void Texture::Blit(const Vec2& position, BYTE* screenPtr, const Rect& screenRect, const float angle)
{
	Rect texRect((int)position.x_, (int)position.y_, width_, height_);

	if (!texRect.Intersects(screenRect))
		return;

	texRect.ClipTo(screenRect);

	BYTE* texOffset = data_ + ((texRect.left_ - (int)position.x_) + (texRect.top_ - (int)position.y_) * width_) * 4;

	int lineJump = (screenRect.Width() - texRect.Width()) * 4;
	int texJump = (width_ - texRect.Width()) * 4;

	float cosangle = cos(-angle);
	float sinangle = sin(-angle);

	int hWidth = (int)(width_ * 0.5f);
	int hHeight = (int)(height_ * 0.5f);

	int swidth = screenRect.Width();

	for (int ty = 0; ty < texRect.Height(); ty++)
	{
		for (int tx = 0; tx < texRect.Width(); tx++)
		{
			int ox = tx - hWidth;
			int oy = ty - hHeight;
			
			int newX = (int)roundf(texRect.left_ + hWidth +(ox * cosangle - oy * sinangle));
			int newY = (int)roundf(texRect.top_ + hHeight + (ox * sinangle + oy * cosangle));

			BYTE* scrOffset = screenPtr + (newX + newY * swidth) * 4;
			memcpy(scrOffset, texOffset, 4);
			texOffset += 4;
		}
		texOffset += texJump;
	}
}

void Texture::BlitAlpha(const Vec2& position, BYTE* screenPtr, const Rect& screenRect)
{
	Rect texRect((int)position.x_, (int)position.y_, width_, height_);

	if (!texRect.Intersects(screenRect))
		return;

	texRect.ClipTo(screenRect);

	BYTE* scrOffset = screenPtr + (texRect.left_ + texRect.top_ * screenRect.Width()) * 4;
	BYTE* texOffset = data_ + ((texRect.left_ - (int)position.x_) + (texRect.top_ - (int)position.y_) * width_) * 4;

	int lineJump = (screenRect.Width() - texRect.Width()) * 4;
	int texJump = (width_ - texRect.Width()) * 4;

	//For each pixel in the texture, multiply it by its alpha, then the pixel at the same place on the screen
	//Then copy the final value in.
	for (int ty = 0; ty < texRect.Height(); ty++)
	{
		for (int tx = 0; tx < texRect.Width(); tx++)
		{
			BYTE a = texOffset[3];

			if (a == 255)
			{
				memcpy(scrOffset, texOffset, 4);
			}
			else if (a > 0)
			{
				scrOffset[0] = scrOffset[0] + ((a * (texOffset[0] - scrOffset[0])) >> 8);
				scrOffset[1] = scrOffset[1] + ((a * (texOffset[1] - scrOffset[1])) >> 8);
				scrOffset[2] = scrOffset[2] + ((a * (texOffset[2] - scrOffset[2])) >> 8);
			}

			texOffset += 4;
			scrOffset += 4;
		}
		texOffset += texJump;
		scrOffset += lineJump;
	}
}

void Texture::BlitAnimated(const Vec2& position, BYTE* screenPtr, const Rect& screenRect, Animation* animation)
{
	Rect frame = animation->GetFrameRect();

	Rect texRect((int)position.x_, (int)position.y_, frame.Width(), frame.Height());

	if (!texRect.Intersects(screenRect))
		return;

	texRect.ClipTo(screenRect);

	BYTE* scrOffset = screenPtr + (texRect.left_ + texRect.top_ * screenRect.Width()) * 4;
	BYTE* texOffset = data_ + (((texRect.left_ - (int)position.x_) + frame.left_) + ((texRect.top_ - (int)position.y_) + frame.top_) * width_) * 4;

	int lineJump = (screenRect.Width() - texRect.Width()) * 4;
	int texJump = (width_ - texRect.Width()) * 4;

	//For each pixel in the texture, multiply it by its alpha, then the pixel at the same place on the screen
	//Then copy the final value in.
	for (int ty = 0; ty < texRect.Height(); ty++)
	{
		for (int tx = 0; tx < texRect.Width(); tx++)
		{
			BYTE a = texOffset[3];

			if (a == 255)
			{
				memcpy(scrOffset, texOffset, 4);
			}
			else if (a > 0)
			{
				scrOffset[0] = scrOffset[0] + ((a * (texOffset[0] - scrOffset[0])) >> 8);
				scrOffset[1] = scrOffset[1] + ((a * (texOffset[1] - scrOffset[1])) >> 8);
				scrOffset[2] = scrOffset[2] + ((a * (texOffset[2] - scrOffset[2])) >> 8);
			}
 
			texOffset += 4;
			scrOffset += 4;
		}
		texOffset += texJump;
		scrOffset += lineJump;
	}
}
