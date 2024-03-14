#include "GameOverLevel.h"
#include "EnumClass.h"
#include "GameOverUI.h"
#include "SoundManager.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/EngineCore.h>
#include "PlayerInfoManager.h"
#include "ChangingLevel.h"

UGameOverLevel::UGameOverLevel()
{
}

UGameOverLevel::~UGameOverLevel()
{
}

void UGameOverLevel::BeginPlay()
{
	ULevel::BeginPlay();

	GameOverUI = SpawnActor<AGameOverUI>(static_cast<int>(EActorType::UI));
	USoundManager::GetInst().EffectSoundPlay("GameOver.wav");
}

void UGameOverLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_RETURN))
	{
		std::string LevelName = GetName();
		GEngine->DestroyLevel(LevelName);
		GEngine->CreateLevel<UChangingLevel>("ReStart");
		GEngine->ChangeLevel("ReStart");
	}
}

