#pragma once
#include <string>
#include <string_view>
#include <EngineBase\EnginePath.h>
#include <map>

#include "ThirdParty\FMOD\inc\fmod.hpp"

// Ό³Έν :
class UEngineSound
{
private:
	static std::map<std::string, UEngineSound*> Resources;

public:
	// constrcuter destructer
	UEngineSound();
	~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view _Path)
	{
		UEnginePath NewPath = UEnginePath(std::filesystem::path(_Path));
		std::string FileName = NewPath.GetFileName();
		return Load(_Path, FileName);
	}

	static void Load(std::string_view _Path, std::string_view _Name);

	static void ResourcesRelease();

protected:

private:
	FMOD::Sound* SoundHandle = nullptr;

};

