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
}

void ACastleBridge::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}
