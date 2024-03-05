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
	for (int i = 0; i < UInGameValue::TimeRendererSize; i++)
	{
		UImageRenderer* Renderer= CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
		TimeRenderer.push_back(Renderer);
		TimeRenderer[i]->SetImage("Numbers.png");
		FVector UITimeScale = TimeRenderer[i]->GetImage()->GetScale();
		TimeRenderer[i]->SetTransform({ {252 + 24*i, 24}, {UITimeScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UITimeScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
		TimeRenderer[i]->CameraEffectOff();
		TimeRenderer[i]->CreateAnimation("0", "Numbers.png", 0, 0, false);
		TimeRenderer[i]->CreateAnimation("1", "Numbers.png", 1, 1, false);
		TimeRenderer[i]->CreateAnimation("2", "Numbers.png", 2, 2, false);
		TimeRenderer[i]->CreateAnimation("3", "Numbers.png", 3, 3, false);
		TimeRenderer[i]->CreateAnimation("4", "Numbers.png", 4, 4, false);
		TimeRenderer[i]->CreateAnimation("5", "Numbers.png", 5, 5, false);
		TimeRenderer[i]->CreateAnimation("6", "Numbers.png", 6, 6, false);
		TimeRenderer[i]->CreateAnimation("7", "Numbers.png", 7, 7, false);
		TimeRenderer[i]->CreateAnimation("8", "Numbers.png", 8, 8, false);
		TimeRenderer[i]->CreateAnimation("9", "Numbers.png", 9, 9, false);
	}
}

void AUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	TimeCheck(_DeltaTime);
	TimeRenderUpdate();
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

	if (0.0f >= TimeInterval)
	{	
		--TimeCount;
		// 1초보다 더 지났다면 TimeInterval을 1초로 초기화하는 것이 아닌 더 지난만큼 값을 반영.
		// (정확한 1초를 위함)
		TimeInterval = 1.0f + TimeInterval;
		TimeChange = true;
		return;
	}
}

void AUI::TimeRenderUpdate()
{
	if (true == TimeChange)
	{
		int TempTime = TimeCount;
		int ToStringValue = 0;

		NumberToAnimation(TimeCount, FVector(100, 100), 3, TimeRenderer);

		ToStringValue = TempTime / 100;
		TimeRenderer[0]->ChangeAnimation(std::to_string(ToStringValue));
		TempTime = TempTime % 100;

		ToStringValue = TempTime / 10;
		TimeRenderer[1]->ChangeAnimation(std::to_string(ToStringValue));
		TempTime = TempTime % 10;

		ToStringValue = TempTime;
		TimeRenderer[2]->ChangeAnimation(std::to_string(ToStringValue));

		TimeChange = false;
	}
}

void AUI::NumberToAnimation(int _PrintNumber, const FVector& _InitPos, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer)
{
	if (_Renderer.empty())
	{
		MsgBoxAssert("입력받은 자료 내부가 비어있습니다.");
	}

	int a = 0;

}