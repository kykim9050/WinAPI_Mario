#include "GameOverUI.h"
#include "InGameValue.h"

AGameOverUI::AGameOverUI()
{
}

AGameOverUI::~AGameOverUI()
{
}

void AGameOverUI::BeginPlay()
{
	AUIBaseInfo::BeginPlay();

	UIRenderer->SetImage("GameOver.png");
	FVector UIScale = UIRenderer->GetImage()->GetScale();
	UIRenderer->SetTransform({ {UIScale.ihX() * UInGameValue::WindowSizeMulValue, UIScale.ihY() * UInGameValue::WindowSizeMulValue}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue} });
}

void AGameOverUI::Tick(float _DeltaTime)
{
	AUIBaseInfo::Tick(_DeltaTime);
}