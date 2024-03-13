#include "SoundManager.h"
#include <EngineBase/EngineDebug.h>
#include <EnginePlatform/EngineSound.h>

USoundManager::USoundManager()
{
}

USoundManager::~USoundManager()
{
}

void USoundManager::BGMSoundPlay(const std::string_view _StageInfo)
{
	if ("1-1" == _StageInfo)
	{
		StageBGM = UEngineSound::SoundPlay("1_1StageLevel.mp3");
		return;
	}
	else if ("1-4" == _StageInfo)
	{
		StageBGM = UEngineSound::SoundPlay("1_4StageLevel.mp3");
		return;
	}

	MsgBoxAssert("사운드를 재생하려는데 스테이지의 이름이 적절치 않거나 해당되는 스테이지 BGM사운드가 없습니다.");
	return;
}

void USoundManager::BGMSoundStop()
{
	StageBGM.Off();
}

void USoundManager::EffectSoundPlay(const std::string_view _EffectSoundName)
{
	EffectSound = UEngineSound::SoundPlay(_EffectSoundName);
}
