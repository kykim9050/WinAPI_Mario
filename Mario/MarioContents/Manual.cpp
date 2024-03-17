#include "Manual.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>

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
	ManualRenderer->SetTransform({ {0,0}, {ManualScale.iX(), ManualScale.iY()} });
	ManualRenderer->ActiveOff();
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
			ManualDIsplay = true;
			ManualRenderer->ActiveOn();
			return;
		}

		ManualDIsplay = false;
		ManualRenderer->ActiveOff();
		return;
	}
}