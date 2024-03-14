#include "GameOverLevel.h"
#include "EnumClass.h"
#include "GameOverUI.h"

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
}

void UGameOverLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

