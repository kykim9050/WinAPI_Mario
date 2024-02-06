#include "TitleCoin.h"
#include "ContentsCore.h"

ATitleCoin::ATitleCoin()
{
}

ATitleCoin::~ATitleCoin()
{
}

void ATitleCoin::BeginPlay()
{
	AActor::BeginPlay();

	// Title전용 RendererOrder Enum class만들어야 함
	UImageRenderer* TitleCoinRenderer = CreateImageRenderer(1);
	TitleCoinRenderer->SetImage("TitleCoin.png");
	// 윈도우 사이즈 받아올 수 있도록 수정 필요

	TitleCoinRenderer->SetTransform({ {88 * ContentsCore::WindowSizeMulValue, 24 * ContentsCore::WindowSizeMulValue},{64*ContentsCore::WindowSizeMulValue, 64*ContentsCore::WindowSizeMulValue} });

	// 랜더링이 idx0으로 다시 가면 안되고 0 1 2 1 0 1 2 ... 이런식으로 되어야 함
	TitleCoinRenderer->CreateAnimation("Coin_Twinkle", "TitleCoin.png", 0, 4, 0.15f, true);
	TitleCoinRenderer->ChangeAnimation("Coin_Twinkle");


}

void ATitleCoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}


