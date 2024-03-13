#pragma once
#include <string>
#include <EnginePlatform/EngineSound.h>

// Ό³Έν :
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

	void SoundPlay(const std::string_view _SoundFileName);
	void SoundStop(const std::string_view _SoundFileName);

protected:

private:
	USoundManager();
	~USoundManager();

	UEngineSoundPlayer Player;
};

