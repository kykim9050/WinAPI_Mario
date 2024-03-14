#include "UIBaseInfo.h"

AUIBaseInfo::AUIBaseInfo()
{
}

AUIBaseInfo::~AUIBaseInfo()
{
}

void AUIBaseInfo::BeginPlay()
{
	AActor::BeginPlay();

	for (int i = 0; i < UInGameValue::ScoreRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUIComponent));
		ScoreRenderer.push_back(Renderer);
		ScoreRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = ScoreRenderer[i]->GetImage()->GetScale();
		ScoreRenderer[i]->SetTransform({ {UInGameValue::UIScoreRendInitXPos + UInGameValue::UISpacingBetRends * i, UInGameValue::UIRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
		ScoreRenderer[i]->CameraEffectOff();
		ScoreRenderer[i]->CreateAnimation("0", "Numbers.png", 0, 0, false);
		ScoreRenderer[i]->CreateAnimation("1", "Numbers.png", 1, 1, false);
		ScoreRenderer[i]->CreateAnimation("2", "Numbers.png", 2, 2, false);
		ScoreRenderer[i]->CreateAnimation("3", "Numbers.png", 3, 3, false);
		ScoreRenderer[i]->CreateAnimation("4", "Numbers.png", 4, 4, false);
		ScoreRenderer[i]->CreateAnimation("5", "Numbers.png", 5, 5, false);
		ScoreRenderer[i]->CreateAnimation("6", "Numbers.png", 6, 6, false);
		ScoreRenderer[i]->CreateAnimation("7", "Numbers.png", 7, 7, false);
		ScoreRenderer[i]->CreateAnimation("8", "Numbers.png", 8, 8, false);
		ScoreRenderer[i]->CreateAnimation("9", "Numbers.png", 9, 9, false);
	}
}

void AUIBaseInfo::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}



