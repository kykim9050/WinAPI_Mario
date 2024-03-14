#include "1_4StageLevel.h"
#include "BackGroundMap.h"
#include "CollisionMap.h"
#include "UI.h"
#include <EngineCore/EngineCore.h>
#include "Koopa.h"
#include "FootBoard.h"
#include "CastleBridge.h"
#include "Princess.h"
#include "SignalCollision.h"
#include "RotatingFire.h"

U1_4StageLevel::U1_4StageLevel()
{
}

U1_4StageLevel::~U1_4StageLevel()
{
}

void U1_4StageLevel::BeginPlay()
{
	UStageLevel::BeginPlay();

	Mario->SetActorLocation({ UInGameValue::Stage1_4MarioInitXPos, UInGameValue::Stage1_4MarioInitYPos });

	Map->GetMapRenderer()->SetImage("1_4Stage_Map.png");
	FVector MapImageFVector = Map->GetMapRenderer()->GetImage()->GetScale();
	Map->GetMapRenderer()->SetTransform({ { MapImageFVector.ihX(), MapImageFVector.ihY()}, {MapImageFVector} });

	ColMap->GetColMapRenderer()->SetImage("1_4Stage_CollisionMap.png");
	FVector ColMapImageFVector = ColMap->GetColMapRenderer()->GetImage()->GetScale();
	ColMap->GetColMapRenderer()->SetTransform({ { ColMapImageFVector.ihX(), ColMapImageFVector.ihY()}, {ColMapImageFVector} });

	AKoopa* BossMonsterKoopa = SpawnActor<AKoopa>(static_cast<int>(EActorType::Monster));
	BossMonsterKoopa->SetActorLocation(UInGameValue::KoopaInitPos);

	AFootBoard* FootBoard = SpawnActor<AFootBoard>(static_cast<int>(EActorType::Block));
	FootBoard->SetActorLocation({ UInGameValue::MovingBoardInitXPos, UInGameValue::MovingBoardInitYPos });


	ACastleBridge* CastleBridge = SpawnActor<ACastleBridge>(static_cast<int>(EActorType::Structure));
	CastleBridge->SetActorLocation({ UInGameValue::BridgeStartXPos, UInGameValue::BridgeStartYPos });

	APrincess* Princess = SpawnActor<APrincess>(static_cast<int>(EActorType::Player));

	USignalCollision* BossRoomStartLine = SpawnActor<USignalCollision>(static_cast<int>(EActorType::Structure));
	BossRoomStartLine->SetActorLocation(UInGameValue::BossRoomStartLineInitPos);

	ARotatingFire* Trap1 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	ARotatingFire* Trap2 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	ARotatingFire* Trap3 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	ARotatingFire* Trap4 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	ARotatingFire* Trap5 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	ARotatingFire* Trap6 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	ARotatingFire* Trap7 = SpawnActor<ARotatingFire>(static_cast<int>(EActorType::AttackableTrap));
	
	Trap1->SetActorLocation({ 1464, 504 });
	Trap2->SetActorLocation({ 2376, 312 });
	Trap3->SetActorLocation({ 2904, 312 });
	Trap4->SetActorLocation({ 3240, 312 });
	Trap5->SetActorLocation({ 3672, 456 });
	Trap6->SetActorLocation({ 4056, 456 });
	Trap7->SetActorLocation({ 4248, 216 });
	

}

void U1_4StageLevel::Tick(float _DeltaTime)
{
	UStageLevel::Tick(_DeltaTime);
}

