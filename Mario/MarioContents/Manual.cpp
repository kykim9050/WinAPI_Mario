#include "Manual.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>
#include "InGameValue.h"

AManual::AManual()
{
}

AManual::~AManual()
{
}

void AManual::BeginPlay()
{
	AActor::BeginPlay();

	ManualRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Manual));
	ManualRenderer->SetImage("Manual.png");

	FVector ManualScale = ManualRenderer->GetImage()->GetScale();
	ManualRenderer->SetTransform({ {static_cast<int>(UInGameValue::ResultMainWindowXScale / 2) , static_cast<int>(UInGameValue::ResultMainWindowYScale / 2)}, {UInGameValue::ResultMainWindowXScale, UInGameValue::ResultMainWindowYScale} });
	ManualRenderer->ActiveOff();
	ManualRenderer->CameraEffectOff();
}

void AManual::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	ManualDisplayCheck();
}

void AManual::ManualDisplayCheck()
{
	if (true == UEngineInput::IsDown('M'))
	{
		if (false == ManualDIsplay)
		{
			GetWorld()->SetAllTimeScale(0.0f);
			ManualDIsplay = true;
			ManualRenderer->ActiveOn();
			return;
		}

		GetWorld()->SetAllTimeScale(1.0f);
		ManualDIsplay = false;
		ManualRenderer->ActiveOff();
		return;
	}
}