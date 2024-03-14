#include "TimeUpUI.h"
#include "InGameValue.h"

ATimeUpUI::ATimeUpUI()
{
}

ATimeUpUI::~ATimeUpUI()
{
}

void ATimeUpUI::BeginPlay()
{
	AUIBaseInfo::BeginPlay();

	UIRenderer->SetImage("TimeUp.png");
	FVector UIScale = UIRenderer->GetImage()->GetScale();
	UIRenderer->SetTransform({ {UIScale.ihX() * UInGameValue::WindowSizeMulValue, UIScale.ihY() * UInGameValue::WindowSizeMulValue}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue} });

	NumberToAnimation(IntroScore, 6, ScoreRenderer);
	NumberToAnimation(IntroAmountOfCoins, 2, CoinCountRenderer);

	for (int i = 0; i < UInGameValue::StageInfoRendererSize; i++)
	{
		StageInfoRenderer[i]->ChangeAnimation(IntroStageInfo[i]);
		StageInfoRenderer[i]->ChangeAnimation(IntroStageInfo[i]);
	}
}

void ATimeUpUI::Tick(float _DeltaTime)
{
	AUIBaseInfo::Tick(_DeltaTime);
}
