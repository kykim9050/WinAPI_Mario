#include "BridgeBlock.h"

ABridgeBlock::ABridgeBlock()
{
}

ABridgeBlock::~ABridgeBlock()
{
}

void ABridgeBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	Renderer->SetImage("CastleBridgeBlock.png");

	FVector BridgeBlockScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {BridgeBlockScale.iX() * UInGameValue::WindowSizeMulValue, BridgeBlockScale.iY() * UInGameValue::WindowSizeMulValue} });

}

void ABridgeBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

