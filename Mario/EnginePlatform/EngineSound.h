#pragma once
#include <string>
#include <string_view>

#include "ThirdParty\FMOD\inc\fmod.hpp"

// Ό³Έν :
class UEngineSound
{
public:
	// constrcuter destructer
	UEngineSound();
	~UEngineSound();

	// delete Function
	UEngineSound(const UEngineSound& _Other) = delete;
	UEngineSound(UEngineSound&& _Other) noexcept = delete;
	UEngineSound& operator=(const UEngineSound& _Other) = delete;
	UEngineSound& operator=(UEngineSound&& _Other) noexcept = delete;

	static void Load(std::string_view _Path, std::string_view _Name);

protected:

private:
	FMOD::Sound* SoundHandle = nullptr;

};

