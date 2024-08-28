#include "TimeUpLevel.h"
#include "TimeUpUI.h"
#include "EnumClass.h"
#include <EngineCore/EngineCore.h>
#include "LoadingLevel.h"

UTimeUpLevel::UTimeUpLevel()
{
}

UTimeUpLevel::~UTimeUpLevel()
{
}

void UTimeUpLevel::BeginPlay()
{
	ULevel::BeginPlay();

	TimeUpUI = SpawnActor<ATimeUpUI>(static_cast<int>(EActorType::UI));
}

void UTimeUpLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	ReturnToStage(_DeltaTime);
}

void UTimeUpLevel::ReturnToStage(float _DeltaTime)
{
	static float DelayTime = 3.0f;

	DelayTime -= _DeltaTime;

	if (0.0f >= DelayTime)
	{
		DelayTime = 3.0f;

		std::string LevelName = GetName();
		GEngine->DestroyLevel(LevelName);
		GEngine->CreateLevel<ULoadingLevel>("PlayerDead");
		GEngine->ChangeLevel("PlayerDead");
		return;
	}
}


