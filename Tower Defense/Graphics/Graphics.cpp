#include <Graphics/Graphics.h>

#include <Graphics/Texture.h>
#include <Graphics/Animation.h>
#include <Math/Rect.h>
#include <World/World.h>

Graphics* Graphics::instance_ = nullptr;

Graphics* Graphics::Instance()
{
	if (instance_ == nullptr)
		instance_ = new Graphics();

	return instance_;
}

Graphics::Graphics()
{	

}

Graphics::~Graphics()
{
	for (auto iterator : textures_)
	{
		delete iterator.second;
	}

	for (Animation* animation : animations_)
	{
		delete animation;
	}
}

void Graphics::Initialise(int screenWidth, int screenHeight)
{
	scrWidth_ = screenWidth;
	scrHeight_ = screenHeight;
	screenRect = Rect(0, 0, scrWidth_, scrHeight_);

	if (!HAPI->Initialise(&scrWidth_, &scrHeight_))
		return;

	screenPtr_ = HAPI->GetScreenPointer();	
}

void Graphics::LoadTexture(std::string loadPath, std::string uid)
{
	Texture* texture = new Texture(loadPath);
	textures_[uid] = texture;
}

void Graphics::CreateTexture(Colour& colour, int width, int height, std::string uid)
{
	Texture* texture = new Texture(width, height);
	texture->Fill(colour);
}

int Graphics::CreateAnimation(int startFrame, int endFrame, int frameWidth, int frameHeight, int framesAcross, int framesDown, int fps)
{
	Animation* a = new Animation(startFrame, endFrame, frameWidth, frameHeight, framesAcross, framesDown, fps);
	animations_.push_back(a);
	return animations_.size() - 1;
}

int Graphics::CopyAnimation(int animID)
{
	Animation* old = animations_[animID];
	Animation* newAnim = new Animation(old->startFrame_, old->endFrame_, old->frameWidth_, old->frameHeight_, old->framesAcross_, old->framesDown_, old->fps_);
	animations_.push_back(newAnim);
	return animations_.size() - 1;
}

void Graphics::UpdateAnimation(const int animID, float delta)
{
	if (animID == -1)
		return;
	animations_[animID]->Update(delta);
}

void Graphics::SetClearColour(float r, float g, float b)
{
	clearColour_.r = (BYTE)r;
	clearColour_.g = (BYTE)g;
	clearColour_.b = (BYTE)b;
}

void Graphics::Clear()
{
	if (clearColour_.r == clearColour_.g && clearColour_.r == clearColour_.b)
	{
		memset(screenPtr_, clearColour_.r, (scrWidth_ * scrHeight_) << 2);
	}
	else
	{
		for (int offset = 0; offset < scrWidth_ * scrHeight_; offset++)
		{
			memcpy(screenPtr_ + offset * 4, &clearColour_, 4);
		}
	}
}

Colour Graphics::PixelAt(const Vec2& position)
{
	BYTE* offset = screenPtr_ + ((int)position.x_ + (int)position.y_ * scrWidth_) * 4;
	return Colour((int)offset[2], (int)offset[1], (int)offset[0], (int)offset[3]);
}

Colour Graphics::PixelAt(const Vec2& position, const std::string uid)
{
	if (textures_.find(uid) == textures_.end())
		return Colour(0, 0, 0);

	Texture* texture = textures_[uid];
	return texture->PixelAt(position);
}

void Graphics::Blit(const Vec2& position, const std::string& uid, int width = 0, int height = 0)
{
	if (textures_.find(uid) == textures_.end())
		return;

	Texture* texture = textures_[uid];
	texture->Blit(position, screenPtr_, screenRect, width, height);
}

void Graphics::Blit(const Vec2& position, const std::string& uid, const float angle)
{
	if (textures_.find(uid) == textures_.end())
		return;

	Texture* texture = textures_[uid];
	texture->Blit(position, screenPtr_, screenRect, angle);
}

void Graphics::ClipBlit(const Vec2& position, const std::string& uid, int width, int height)
{	
	if (textures_.find(uid) == textures_.end())
		return;

	Texture* texture = textures_[uid];
	texture->ClipBlit(position, screenPtr_, screenRect, width, height);
}

void Graphics::BlitRect(Rect rect, const Colour& colour)
{

	if (!rect.Intersects(screenRect))
		return;

	rect.ClipTo(screenRect);

	BYTE* screenOffset = screenPtr_ + (rect.left_ + rect.top_ * screenRect.Width()) * 4;	

	int bytesWide = rect.Width() * 4;

	int lineJump = screenRect.Width() * 4 - rect.Width() * 4;
	
	for (int y = 0; y < rect.Height(); y++)	
	{
		if (y == 0 || y == rect.Height() - 1)
		{
			memset(screenOffset, 0, rect.Width() * 4);
			screenOffset += rect.Width() * 4;
		}
		else
		{
			for (int x = 0; x < rect.Width(); x++)
			{
				if (x == 0 || x == rect.Width() - 1)
					memset(screenOffset, 0, 4);
				else
					memcpy(screenOffset, &colour, 4);

				screenOffset += 4;
			}
		}
		screenOffset += lineJump;
	}
}

void Graphics::BlitAlpha(const Vec2& position, const std::string& uid)
{
	if (textures_.find(uid) == textures_.end())
		return;

	Texture* texture = textures_[uid];
	Rect screenRect(0, 0, scrWidth_, scrHeight_);
	texture->BlitAlpha(position, screenPtr_, screenRect);
}

void Graphics::BlitAnimated(const Vec2& position, const std::string& texID, const int animID)
{
	if (textures_.find(texID) == textures_.end())
		return;

	Animation* animation = animations_[animID];

	Texture* texture = textures_[texID];
	Rect screenRect(0, 0, scrWidth_, scrHeight_);
	texture->BlitAnimated(position, screenPtr_, screenRect, animation);
}

void Graphics::BlitLine(const Vec2& p1, const Vec2& p2, const Colour& colour) // adam wishes to know why -.-
{
	int x1 = (int)p1.x_;
	int y1 = (int)p1.y_;
	int x2 = (int)p2.x_;
	int y2 = (int)p2.y_;

	int x, y, dx, dy, dx1, dy1, px, py, xe, ye, i;
	dx = x2 - x1;
	dy = y2 - y1;
	dx1 = (int)fabs((float)dx);
	dy1 = (int)fabs((float)dy);
	px = 2 * dy1 - dx1;
	py = 2 * dx1 - dy1;
	if (dy1 <= dx1)
	{
		if (dx >= 0)
		{
			x = x1;
			y = y1;
			xe = x2;
		}
		else
		{
			x = x2;
			y = y2;
			xe = x1;
		}
		if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
		{
			BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
			memcpy(offset, &colour, 4);
		}
		for (i = 0; x<xe; i++)
		{
			x = x + 1;
			if (px<0)
			{
				px = px + 2 * dy1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					y = y + 1;
				}
				else
				{
					y = y - 1;
				}
				px = px + 2 * (dy1 - dx1);
			}
			if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
			{
				BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
				memcpy(offset, &colour, 4);
			}
		}
	}
	else
	{
		if (dy >= 0)
		{
			x = x1;
			y = y1;
			ye = y2;
		}
		else
		{
			x = x2;
			y = y2;
			ye = y1;
		}
		if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
		{
			BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
			memcpy(offset, &colour, 4);
		}
		for (i = 0; y<ye; i++)
		{
			y = y + 1;
			if (py <= 0)
			{
				py = py + 2 * dx1;
			}
			else
			{
				if ((dx<0 && dy<0) || (dx>0 && dy>0))
				{
					x = x + 1;
				}
				else
				{
					x = x - 1;
				}
				py = py + 2 * (dx1 - dy1);
			}
			if (x > 0 && x < scrWidth_ && y > 0 && y < scrHeight_)
			{
				BYTE* offset = screenPtr_ + (x + y * scrWidth_) * 4;
				memcpy(offset, &colour, 4);
			}
		}
	}
}

void Graphics::BlitText(const Vec2& position, const std::string& text, const Colour& colour)
{
	HAPI->RenderText((int)position.x_, (int)position.y_, HAPI_TColour(colour.r, colour.g, colour.b), text);
}