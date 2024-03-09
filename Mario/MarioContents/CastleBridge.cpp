#include "CastleBridge.h"
#include "BridgeBlock.h"

ACastleBridge::ACastleBridge()
{

}

ACastleBridge::~ACastleBridge()
{
}

void ACastleBridge::BeginPlay()
{
	AStructureUnit::BeginPlay();

	for (int i = 0; i < UInGameValue::BridgeBlockAmount; i++)
	{
		ABridgeBlock* BridgeBlock = GetWorld()->SpawnActor<ABridgeBlock>(static_cast<int>(EActorType::Block));
		BridgeBlock->SetActorLocation({ UInGameValue::BridgeStartXPos + UInGameValue::BTBDistance * i,  UInGameValue::BridgeStartYPos });
		BridgeBlocks.push_front(BridgeBlock);
	}

	BridgeChainRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	BridgeChainRenderer->SetImage("CastleItems.png");
	FVector CastleItemsScale = BridgeChainRenderer->GetImage()->GetScale();
	BridgeChainRenderer->SetTransform({ { UInGameValue::BTBDistance * (UInGameValue::BridgeBlockAmount - 1), -UInGameValue::BTBDistance}, {CastleItemsScale.iX() / UInGameValue::CastleItemsImgXValue * UInGameValue::WindowSizeMulValue, CastleItemsScale.iY() / UInGameValue::CastleItemsImgYValue * UInGameValue::WindowSizeMulValue} });
	BridgeChainRenderer->CreateAnimation("BridgeChain", "CastleItems.png", 0, 0, 0.1f, false);
	BridgeChainRenderer->ChangeAnimation("BridgeChain");

	BridgeFlagRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	BridgeFlagRenderer->SetImage("CastleItems.png");
	BridgeFlagRenderer->SetTransform({ { UInGameValue::BTBDistance * UInGameValue::BridgeBlockAmount, -(UInGameValue::BTBDistance * 2)}, {CastleItemsScale.iX() / UInGameValue::CastleItemsImgXValue * UInGameValue::WindowSizeMulValue, CastleItemsScale.iY() / UInGameValue::CastleItemsImgYValue * UInGameValue::WindowSizeMulValue} });
	BridgeFlagRenderer->CreateAnimation("BridgeFlag", "CastleItems.png", { 8,8,8,8,9,10,9 }, 0.15f, true);
	BridgeFlagRenderer->ChangeAnimation("BridgeFlag");

	BridgeFlagCollision = CreateCollision(ECollisionOrder::CastleEndFlag);
	BridgeFlagCollision->SetTransform({ { UInGameValue::BTBDistance * UInGameValue::BridgeBlockAmount, -(UInGameValue::BTBDistance * 2)}, {UInGameValue::CastleEndFlagXScale, UInGameValue::CastleEndFlagYScale } });
	BridgeFlagCollision->SetColType(ECollisionType::Rect);
}

void ACastleBridge::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}
