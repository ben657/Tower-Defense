#pragma once

#include <HAPI_lib.h>
#include <map>

class Audio
{
private:
	static Audio* instance_;

	std::map<std::string, int> sounds_;

protected:
	Audio();

public:
	static Audio* Instance();
	
	~Audio();

	void LoadSound(const std::string& file, const std::string& name);
	void PlaySound(const std::string& name, bool loop, int volume);
	void StopSound(const std::string& name);
};

#define audio Audio::Instance()