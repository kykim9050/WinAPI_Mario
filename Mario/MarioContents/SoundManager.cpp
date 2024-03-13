#include "SoundManager.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineSound.h>

USoundManager::USoundManager()
{
}

USoundManager::~USoundManager()
{
}

void USoundManager::SoundPlay(const std::string_view _SoundFileName)
{
	UEngineSoundPlayer Player = UEngineSound::SoundPlay(_SoundFileName);
}