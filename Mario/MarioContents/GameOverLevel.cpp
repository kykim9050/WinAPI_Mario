#include "GameOverLevel.h"
#include "EnumClass.h"
#include "GameOverUI.h"
#include "SoundManager.h"

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
}

