#include "IntroLevel.h"
#include "BackGroundMap.h"

UIntroLevel::UIntroLevel()
{
}

UIntroLevel::~UIntroLevel()
{
}

void UIntroLevel::BeginPlay()
{
	ULevel::BeginPlay();

	Map = SpawnActor<ABackGroundMap>(static_cast<int>(EActorType::Map));
	Map->GetMapRenderer()->SetImage("LevelIntro.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX() * UInGameValue::WindowSizeMulValue, MapImageFVector.ihY() * UInGameValue::WindowSizeMulValue}, {MapImageFVector.iX() *UInGameValue::WindowSizeMulValue, MapImageFVector.iY() * UInGameValue::WindowSizeMulValue}});
}

void UIntroLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}

void UIntroLevel::LevelStart(ULevel* _PrevLevel)
{
	ULevel::LevelStart(_PrevLevel);
}

void UIntroLevel::LevelEnd(ULevel* _NextLevel)
{
	ULevel::LevelEnd(_NextLevel);
}
