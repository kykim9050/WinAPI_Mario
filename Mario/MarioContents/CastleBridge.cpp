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
	FVector BridgeChainScale = BridgeChainRenderer->GetImage()->GetScale();
	BridgeChainRenderer->SetTransform({ { UInGameValue::BTBDistance * (UInGameValue::BridgeBlockAmount - 1), -UInGameValue::BTBDistance}, {BridgeChainScale.iX() / UInGameValue::CastleItemsImgXValue * UInGameValue::WindowSizeMulValue, BridgeChainScale.iY() / UInGameValue::CastleItemsImgYValue * UInGameValue::WindowSizeMulValue} });
	BridgeChainRenderer->CreateAnimation("BridgeChain", "CastleItems.png", 0, 0, 0.1f, false);
	BridgeChainRenderer->ChangeAnimation("BridgeChain");



}

void ACastleBridge::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}
