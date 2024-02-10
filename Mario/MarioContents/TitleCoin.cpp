#include "TitleCoin.h"
#include "ContentsCore.h"
#include "EnumClass.h"
#include "InGameValue.h"

ATitleCoin::ATitleCoin()
{
}

ATitleCoin::~ATitleCoin()
{
}

void ATitleCoin::BeginPlay()
{
	AActor::BeginPlay();


	UImageRenderer* TitleCoinRenderer = CreateImageRenderer(static_cast<int>(ETitleRenderOrder::Coin));
	TitleCoinRenderer->SetImage("TitleCoin.png");


	TitleCoinRenderer->SetTransform({ {88 * UInGameValue::WindowSizeMulValue, 24 * UInGameValue::WindowSizeMulValue},{64,64} });
	TitleCoinRenderer->CreateAnimation("Coin_Twinkle", "TitleCoin.png", 0, 5, 0.15f, true);
	TitleCoinRenderer->ChangeAnimation("Coin_Twinkle");


}

void ATitleCoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}


