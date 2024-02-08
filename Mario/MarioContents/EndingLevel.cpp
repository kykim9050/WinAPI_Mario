#include "EndingLevel.h"
#include "EndingBackGround.h"

UEndingLevel::UEndingLevel()
{
}

UEndingLevel::~UEndingLevel()
{
}

void UEndingLevel::BeginPlay()
{
	ULevel::BeginPlay();
	AEndingBackGround* BackGround = SpawnActor<AEndingBackGround>();
}

void UEndingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
