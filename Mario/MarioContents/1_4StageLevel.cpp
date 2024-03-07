#include "1_4StageLevel.h"
#include "EndingLevel.h"
#include "BackGroundMap.h"
#include "CollisionMap.h"
#include "UI.h"
#include <EngineCore/EngineCore.h>
#include "Koopa.h"

U1_4StageLevel::U1_4StageLevel()
{
}

U1_4StageLevel::~U1_4StageLevel()
{
}

void U1_4StageLevel::BeginPlay()
{
	UStageLevel::BeginPlay();

	Map->GetMapRenderer()->SetImage("1_4Stage_Map.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX(), MapImageFVector.ihY()}, {MapImageFVector} });

	ColMap->GetColMapRenderer()->SetImage("1_4Stage_CollisionMap.png");
	FVector ColMapImageFVector = ColMap->GetColMapRenderer()->GetImage()->GetScale();
	ColMap->GetColMapRenderer()->SetTransform({ { ColMapImageFVector.ihX(), ColMapImageFVector.ihY()}, {ColMapImageFVector} });

	Mario->SetActorLocation({ UInGameValue::MarioInitXPos, UInGameValue::MarioInitYPos });

	AKoopa* BossMonsterKoopa = SpawnActor<AKoopa>(static_cast<int>(EActorType::Monster));
	BossMonsterKoopa->SetActorLocation({ 300, 300 });

}

void U1_4StageLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);

	if (UEngineInput::IsDown(VK_RETURN))
	{
		GEngine->CreateLevel<UEndingLevel>("Ending");
		GEngine->ChangeLevel("Ending");
	}
}

