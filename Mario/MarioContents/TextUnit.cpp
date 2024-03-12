#include "TextUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"

ATextUnit::ATextUnit()
{
}

ATextUnit::~ATextUnit()
{
}

void ATextUnit::BeginPlay()
{
	AActor::BeginPlay();

	TextRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Score));
	TextRenderer->SetImage("Score.png");
	FVector TextScale = TextRenderer->GetImage()->GetScale();
	TextRenderer->SetTransform({ { 0,0 } ,{ TextScale.iX() / UInGameValue::ScoreImgXValue * UInGameValue::WindowSizeMulValue, TextScale.iY() / UInGameValue::ScoreImgYValue * UInGameValue::WindowSizeMulValue } });
	TextRenderer->CreateAnimation("100", "Score.png", 0, 0, 0.1f, false);
	TextRenderer->CreateAnimation("200", "Score.png", 1, 1, 0.1f, false);
	TextRenderer->CreateAnimation("400", "Score.png", 2, 2, 0.1f, false);
	TextRenderer->CreateAnimation("500", "Score.png", 3, 3, 0.1f, false);
	TextRenderer->CreateAnimation("800", "Score.png", 10, 10, 0.1f, false);
	TextRenderer->CreateAnimation("1000", "Score.png", 4, 4, 0.1f, false);
	TextRenderer->CreateAnimation("2000", "Score.png", 5, 5, 0.1f, false);
	TextRenderer->CreateAnimation("4000", "Score.png", 6, 6, 0.1f, false);
	TextRenderer->CreateAnimation("5000", "Score.png", 7, 7, 0.1f, false);
	TextRenderer->CreateAnimation("8000", "Score.png", 8, 8, 0.1f, false);
	TextRenderer->CreateAnimation("1UP", "Score.png", 9, 9, 0.1f, false);
}

void ATextUnit::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	MoveUpdate(_DeltaTime, GetRisingSpeed());
	
}

void ATextUnit::SetScoreAnimation(int _ScoreValue)
{
	std::string ScoreStr = std::to_string(_ScoreValue);

	TextRenderer->ChangeAnimation(ScoreStr);
}

void ATextUnit::SetLocation(FVector _InitPos)
{
	TextRenderer->SetPosition(_InitPos);
}

void ATextUnit::MoveUpdate(float _Deltatime, float _Speed)
{
	AddActorLocation(FVector::Up * _Deltatime * _Speed);
}