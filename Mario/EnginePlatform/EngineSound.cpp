#include "EngineSound.h"

#pragma comment(lib, "ThirdParty\\FMOD\\inc\\fmod_vc.lib")

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
}


void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	UEngineSound* NewSound = new UEngineSound();
}