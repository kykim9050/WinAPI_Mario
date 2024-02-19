#include "UI.h"
#include "EnumClass.h"
#include "InGameValue.h"

AUI::AUI()
{
}

AUI::~AUI()
{
}

void AUI::BeginPlay()
{
	AActor::BeginPlay();

	PlayerUIRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UI));
	PlayerUIRenderer->SetImage("UIBar.png");

	FVector UIScale = PlayerUIRenderer->GetImage()->GetScale();
	PlayerUIRenderer->SetTransform({ {0,0}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue} });

	PlayerUIRenderer->CameraEffectOff();
}

void AUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
