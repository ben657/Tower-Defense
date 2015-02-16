#include "Audio.h"

Audio* Audio::instance_ = nullptr;

Audio* Audio::Instance()
{
	if (instance_ == nullptr)
		instance_ = new Audio();

	return instance_;
}

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::LoadSound(const std::string& file, const std::string& name)
{
	int id = 0;
	HAPI->LoadSound(file, &id);
	sounds_[name] = id;
}

void Audio::PlaySound(const std::string& name, bool loop, int volume)
{
	int id = sounds_[name];
	HAPI->PlayASound(id, loop, volume);
}

void Audio::StopSound(const std::string& name)
{
	int id = sounds_[name];
	HAPI->StopSound(id);
}