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


	// 숫자 나타나는 초기 위치는 현재 BackGround 기준 (252,24) -> 현재 숫자 이미지는 좌측 상단이 중심
	// 숫자 한칸 사이의 간격은 24씩 X값에 가감하면 된다.
	TimeRenderer1 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
	TimeRenderer1->SetImage("Numbers.png");
	FVector UITimeScale = TimeRenderer1->GetImage()->GetScale();
	TimeRenderer1->SetTransform({ {252, 24}, {UITimeScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UITimeScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue}});
	TimeRenderer1->CameraEffectOff();
	TimeRenderer1->CreateAnimation("0", "Numbers.png", 0, 0, false);
	TimeRenderer1->CreateAnimation("1", "Numbers.png", 1, 1, false);
	TimeRenderer1->CreateAnimation("2", "Numbers.png", 2, 2, false);
	TimeRenderer1->CreateAnimation("3", "Numbers.png", 3, 3, false);
	TimeRenderer1->CreateAnimation("4", "Numbers.png", 4, 4, false);
	TimeRenderer1->CreateAnimation("5", "Numbers.png", 5, 5, false);
	TimeRenderer1->CreateAnimation("6", "Numbers.png", 6, 6, false);
	TimeRenderer1->CreateAnimation("7", "Numbers.png", 7, 7, false);
	TimeRenderer1->CreateAnimation("8", "Numbers.png", 8, 8, false);
	TimeRenderer1->CreateAnimation("9", "Numbers.png", 9, 9, false);

	TimeRenderer2 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
	TimeRenderer2->SetImage("Numbers.png");
	TimeRenderer2->SetTransform({ {252+24, 24}, {UITimeScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UITimeScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
	TimeRenderer2->CameraEffectOff();
	TimeRenderer2->CreateAnimation("0", "Numbers.png", 0, 0, false);
	TimeRenderer2->CreateAnimation("1", "Numbers.png", 1, 1, false);
	TimeRenderer2->CreateAnimation("2", "Numbers.png", 2, 2, false);
	TimeRenderer2->CreateAnimation("3", "Numbers.png", 3, 3, false);
	TimeRenderer2->CreateAnimation("4", "Numbers.png", 4, 4, false);
	TimeRenderer2->CreateAnimation("5", "Numbers.png", 5, 5, false);
	TimeRenderer2->CreateAnimation("6", "Numbers.png", 6, 6, false);
	TimeRenderer2->CreateAnimation("7", "Numbers.png", 7, 7, false);
	TimeRenderer2->CreateAnimation("8", "Numbers.png", 8, 8, false);
	TimeRenderer2->CreateAnimation("9", "Numbers.png", 9, 9, false);

	TimeRenderer3 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
	TimeRenderer3->SetImage("Numbers.png");
	TimeRenderer3->SetTransform({ {252+ 24+ 24, 24}, {UITimeScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UITimeScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
	TimeRenderer3->CameraEffectOff();
	TimeRenderer3->CreateAnimation("0", "Numbers.png", 0, 0, false);
	TimeRenderer3->CreateAnimation("1", "Numbers.png", 1, 1, false);
	TimeRenderer3->CreateAnimation("2", "Numbers.png", 2, 2, false);
	TimeRenderer3->CreateAnimation("3", "Numbers.png", 3, 3, false);
	TimeRenderer3->CreateAnimation("4", "Numbers.png", 4, 4, false);
	TimeRenderer3->CreateAnimation("5", "Numbers.png", 5, 5, false);
	TimeRenderer3->CreateAnimation("6", "Numbers.png", 6, 6, false);
	TimeRenderer3->CreateAnimation("7", "Numbers.png", 7, 7, false);
	TimeRenderer3->CreateAnimation("8", "Numbers.png", 8, 8, false);
	TimeRenderer3->CreateAnimation("9", "Numbers.png", 9, 9, false);

}

void AUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	TimeCheck(_DeltaTime);
	// TimeRenderUpdate();
	// ScoreCheck();
	// ScoreRenderUpdate();
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

	static int i = 0;
	if (0.0f >= TimeInterval)
	{	
		--TimeCount;

		TimeRenderer1->ChangeAnimation(std::to_string(i));
		TimeRenderer2->ChangeAnimation(std::to_string(i));
		TimeRenderer3->ChangeAnimation(std::to_string(i));
		++i;

		// 1초보다 더 지났다면 TimeInterval을 1초로 초기화하는 것이 아닌 더 지난만큼 값을 반영.
		// (정확한 1초를 위함)
		TimeInterval = 1.0f + TimeInterval;
		return;
	}
}
