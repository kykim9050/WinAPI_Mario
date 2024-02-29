#include "EndingLevel.h"
#include "EndingBackGround.h"
#include "EndingMessage.h"

UEndingLevel::UEndingLevel()
{
}

UEndingLevel::~UEndingLevel()
{
}

void UEndingLevel::BeginPlay()
{
	ULevel::BeginPlay();
	AEndingBackGround* BackGround = SpawnActor<AEndingBackGround>(static_cast<int>(EActorType::Map));
	AEndingMessage* Message = SpawnActor<AEndingMessage>();
}

void UEndingLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}
