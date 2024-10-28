#pragma once
#include <string>
#include <EnginePlatform/EngineSound.h>

// ���� :
class USoundManager
{
public:
	// delete Function
	USoundManager(const USoundManager& _Other) = delete;
	USoundManager(USoundManager&& _Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& _Other) = delete;
	USoundManager& operator=(USoundManager&& _Other) noexcept = delete;
	
	static USoundManager& GetInst()
	{
		static USoundManager Inst = USoundManager();
		return Inst;
	}

	void BGMSoundPlay(const std::string_view _StageInfo);
	void BGMSoundStop();

protected:

private:
	USoundManager();
	~USoundManager();

	UEngineSoundPlayer StageBGM;
};

