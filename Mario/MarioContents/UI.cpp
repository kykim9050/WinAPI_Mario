#include "UI.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "PlayerMario.h"
#include "PlayerInfoManager.h"

bool AUI::CalTimeToScoreEnd = false;

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
	PlayerUIRenderer->SetTransform({ {UIScale.ihX()* UInGameValue::WindowSizeMulValue, UIScale.ihY() * UInGameValue::WindowSizeMulValue}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue}});
	PlayerUIRenderer->CameraEffectOff();

	UICoinRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
	UICoinRenderer->SetImage("UICoin.png");
	FVector UICoinScale = UICoinRenderer->GetImage()->GetScale();
	UICoinRenderer->SetTransform({ {UInGameValue::UICoinRendInitXPos + UInGameValue::UISpacingBetRends * 8 ,UInGameValue::UIRendInitYPos}, {UICoinScale.iX() / UInGameValue::UICoinImageXValue * UInGameValue::WindowSizeMulValue, UICoinScale.iY() / UInGameValue::UICoinImageYValue * UInGameValue::WindowSizeMulValue} });
	UICoinRenderer->CameraEffectOff();
	UICoinRenderer->CreateAnimation("Twinkle", "UICoin.png", { 0,1,2,1,0,0 }, 0.15f, true);
	UICoinRenderer->ChangeAnimation("Twinkle");

	// 숫자 나타나는 초기 위치는 현재 BackGround 기준 (252,24) -> 현재 숫자 이미지는 좌측 상단이 중심
	// 숫자 한칸 사이의 간격은 24씩 X값에 가감하면 된다.
	for (int i = 0; i < UInGameValue::TimeRendererSize; i++)
	{
		UImageRenderer* Renderer= CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
		TimeRenderer.push_back(Renderer);
		TimeRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = TimeRenderer[i]->GetImage()->GetScale();
		TimeRenderer[i]->SetTransform({ {UInGameValue::UITtimeRendInitXPos + UInGameValue::UISpacingBetRends * i, UInGameValue::UIRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
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

	for (int i = 0; i < UInGameValue::ScoreRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
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

	for (int i = 0; i < UInGameValue::CoinCountRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
		CoinCountRenderer.push_back(Renderer);
		CoinCountRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = CoinCountRenderer[i]->GetImage()->GetScale();
		CoinCountRenderer[i]->SetTransform({ {UInGameValue::UIScoreRendInitXPos + UInGameValue::UISpacingBetRends * (10+i), UInGameValue::UIRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
		CoinCountRenderer[i]->CameraEffectOff();
		CoinCountRenderer[i]->CreateAnimation("0", "Numbers.png", 0, 0, false);
		CoinCountRenderer[i]->CreateAnimation("1", "Numbers.png", 1, 1, false);
		CoinCountRenderer[i]->CreateAnimation("2", "Numbers.png", 2, 2, false);
		CoinCountRenderer[i]->CreateAnimation("3", "Numbers.png", 3, 3, false);
		CoinCountRenderer[i]->CreateAnimation("4", "Numbers.png", 4, 4, false);
		CoinCountRenderer[i]->CreateAnimation("5", "Numbers.png", 5, 5, false);
		CoinCountRenderer[i]->CreateAnimation("6", "Numbers.png", 6, 6, false);
		CoinCountRenderer[i]->CreateAnimation("7", "Numbers.png", 7, 7, false);
		CoinCountRenderer[i]->CreateAnimation("8", "Numbers.png", 8, 8, false);
		CoinCountRenderer[i]->CreateAnimation("9", "Numbers.png", 9, 9, false);
	}

	for (int i = 0; i < UInGameValue::StageInfoRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
		StageInfoRenderer.push_back(Renderer);
		StageInfoRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = StageInfoRenderer[i]->GetImage()->GetScale();
		StageInfoRenderer[i]->SetTransform({ {UInGameValue::UIStageInfoRendInitXPos + UInGameValue::UISpacingBetRends * (i*2), UInGameValue::UIRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
		StageInfoRenderer[i]->CameraEffectOff();
		StageInfoRenderer[i]->CreateAnimation("0", "Numbers.png", 0, 0, false);
		StageInfoRenderer[i]->CreateAnimation("1", "Numbers.png", 1, 1, false);
		StageInfoRenderer[i]->CreateAnimation("2", "Numbers.png", 2, 2, false);
		StageInfoRenderer[i]->CreateAnimation("3", "Numbers.png", 3, 3, false);
		StageInfoRenderer[i]->CreateAnimation("4", "Numbers.png", 4, 4, false);
		StageInfoRenderer[i]->CreateAnimation("5", "Numbers.png", 5, 5, false);
		StageInfoRenderer[i]->CreateAnimation("6", "Numbers.png", 6, 6, false);
		StageInfoRenderer[i]->CreateAnimation("7", "Numbers.png", 7, 7, false);
		StageInfoRenderer[i]->CreateAnimation("8", "Numbers.png", 8, 8, false);
		StageInfoRenderer[i]->CreateAnimation("9", "Numbers.png", 9, 9, false);
	}

	std::vector<std::string> StageInfo = std::vector<std::string>();
	GetLevelStageInfo(StageInfo);
	UPlayerInfoManager::GetInst().SetStageInfo(StageInfo);

	for (int i = 0; i < UInGameValue::StageInfoRendererSize; i++)
	{
		StageInfoRenderer[i]->ChangeAnimation(StageInfo[i]);
	}

	NumberToAnimation(TimeCount, 3, TimeRenderer);

}

void AUI::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);


	CheckTimeStop();
	if (false == TimeCountPause)
	{
		TimeCheck(_DeltaTime);
	}

	CheckConvertTimeToScore();
	if (true == ConvertTimeToScore)
	{
		CalTimeToScore(_DeltaTime);
		CalTimeToScoreSound(_DeltaTime);
	}

	TimeRenderUpdate();
	ScoreRenderUpdate();
}

void AUI::TimeCheck(float _DeltaTime)
{
	TimeInterval -= _DeltaTime;


	if (0 >= TimeCount)
	{
		TimeCount = 0;

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

		NumberToAnimation(TimeCount, 3, TimeRenderer);

		TimeChange = false;
	}
}

void AUI::NumberToAnimation(int _PrintNumber, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer)
{
	if (_Renderer.empty())
	{
		MsgBoxAssert("입력받은 자료 내부가 비어있습니다.");
	}

	int MaxDigit = 1;

	for (int i = 0; i < _AnimatingNum - 1; i++)
	{
		MaxDigit *= 10;
	}

	int PrintNumber = _PrintNumber;
	int ToStringValue = 0;

	for (int i = 0; i < _AnimatingNum; i++)
	{
		ToStringValue = PrintNumber / MaxDigit;
		_Renderer[i]->ChangeAnimation(std::to_string(ToStringValue));
		PrintNumber = PrintNumber % MaxDigit;
		MaxDigit /= 10;
	}

}

void AUI::ScoreRenderUpdate()
{
	NumberToAnimation(UPlayerInfoManager::GetInst().GetPlayerScore(), 6, ScoreRenderer);
	NumberToAnimation(UPlayerInfoManager::GetInst().GetAmountOfCoins(), 2, CoinCountRenderer);
}


void AUI::GetLevelStageInfo(std::vector<std::string>& _StageInfo)
{
	if (!_StageInfo.empty())
	{
		_StageInfo.clear();
	}


	std::string StageName = GetWorld()->GetName();

	if (StageName.empty())
	{
		MsgBoxAssert("스테이지 이름이 지정되지 않아서 스테이지 정보를 받아올 수 없습니다.");
	}

	std::stringstream StringStream(StageName);
	std::string StrTemp = std::string();

	while (std::getline(StringStream, StrTemp, '-'))
	{
		_StageInfo.push_back(StrTemp);
	}
}

void AUI::CheckTimeStop()
{
	if (true == APlayerMario::GetIsReachingStageEnd())
	{
		TimeCountPause = true;
	}
}

void AUI::CheckConvertTimeToScore()
{
	if (true == APlayerMario::GetIsReachingCastleGate())
	{
		ConvertTimeToScore = true;
	}
}

void AUI::CalTimeToScore(float _DeltaTime)
{
	TTSConvertInterval -= _DeltaTime;

	if (0 >= TimeCount)
	{
		TimeCount = 0;
		ConvertTimeToScore = false;
		SetCalTimeToScoreEnd();
		return;
	}

	if (0.0f >= TTSConvertInterval)
	{
		--TimeCount;
		UPlayerInfoManager::GetInst().AddPlayerScore(50);
		TTSConvertInterval = 0.01f + TTSConvertInterval;
		TimeChange = true;
		return;
	}
}

void AUI::CalTimeToScoreSound(float _DeltaTime)
{
	TTSConvertSoundInterval -= _DeltaTime;

	if (0.0f >= TTSConvertSoundInterval)
	{
		TTSConvertSoundInterval = 0.05f + TTSConvertSoundInterval;
		USoundManager::GetInst().EffectSoundPlay("GetCoin.wav");
	}
}