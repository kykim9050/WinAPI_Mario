#include "TitleCoin.h"
#include "ContentsCore.h"
#include "EnumClass.h"

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
	UImageRenderer* TitleCoinRenderer = CreateImageRenderer(static_cast<int>(TitleRenderOrder::Coin));
	TitleCoinRenderer->SetImage("TitleCoin.png");

	TitleCoinRenderer->SetTransform({ {88 * 3, 24 * 3},{64,64} });
	TitleCoinRenderer->CreateAnimation("Coin_Twinkle", "TitleCoin.png", 0, 5, 0.15f, true);
	TitleCoinRenderer->ChangeAnimation("Coin_Twinkle");


}

void ATitleCoin::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}


