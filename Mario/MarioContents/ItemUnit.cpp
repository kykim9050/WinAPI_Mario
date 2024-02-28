#include "ItemUnit.h"

AItemUnit::AItemUnit()
{
}

AItemUnit::~AItemUnit()
{
}

void AItemUnit::BeginPlay()
{
	AActor::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Coin.png");

	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::CoinImageXValue, ItemScale.iY() / UInGameValue::CoinImageYValue} });
	Renderer->CreateAnimation("Rotating_Coin", "Coin.png", 0, 3, 0.1f, true);
	Renderer->ChangeAnimation("Rotating_Coin");

}

void AItemUnit::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}