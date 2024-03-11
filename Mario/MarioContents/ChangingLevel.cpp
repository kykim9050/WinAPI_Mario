#include "ChangingLevel.h"
#include <EngineCore/EngineCore.h>
#include "TestLevel.h"

UChangingLevel::UChangingLevel()
{
}

UChangingLevel::~UChangingLevel()
{
}

void UChangingLevel::BeginPlay()
{
	ULevel::BeginPlay();
}

void UChangingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	static bool Value = true;
	
	if (true == Value)
	{
		Value = false;
		GEngine->CreateLevel<UTestLevel>("1-4");
		GEngine->ChangeLevel("1-4");
	}
}

void UChangingLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UChangingLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
	std::string LevelName = GetName();
	GEngine->DestroyLevel(LevelName);
}


