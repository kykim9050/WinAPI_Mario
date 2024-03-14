#include "TimeUpLevel.h"
#include "TimeUpUI.h"
#include "EnumClass.h"

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
}



