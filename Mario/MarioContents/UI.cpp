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

	TimeCheck(_DeltaTime);
}

void AUI::TimeCheck(float _DeltaTime)
{
	TimeInterval -= _DeltaTime;

	if (0 >= TimeCount)
	{
		UEngineDebug::OutPutDebugText("Time Out");

		// 타임아웃으로 게임 종료 화면 실행
		return;
	}

	if (0.0f >= TimeInterval)
	{	
		UEngineDebug::OutPutDebugText(std::to_string(TimeCount-1));
		
		// 1초보다 더 지났다면 TimeInterval을 1초로 초기화하는 것이 아닌 더 지난만큼 값을 반영.
		// (정확한 1초를 위함)
		TimeInterval = 1.0f + TimeInterval;
		--TimeCount;
	}
}
