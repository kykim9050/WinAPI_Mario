#include "LevelIntro.h"
#include "PlayerInfoManager.h"
#include "EnumClass.h"
#include "InGameValue.h"

ALevelIntro::ALevelIntro()
{
}

ALevelIntro::~ALevelIntro()
{
}

void ALevelIntro::BeginPlay()
{
	AActor::BeginPlay();

	IntroLife = UPlayerInfoManager::GetInst().GetPlayerLife();
	IntroAmountOfCoins = UPlayerInfoManager::GetInst().GetAmountOfCoins();
	IntroScore = UPlayerInfoManager::GetInst().GetPlayerScore();
	IntroStageInfo = UPlayerInfoManager::GetInst().GetStageInfo();

	UIRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUI));
	UIRenderer->SetImage("LevelIntro.png");
	FVector UIScale = UIRenderer->GetImage()->GetScale();
	UIRenderer->SetTransform({ {UIScale.ihX() * UInGameValue::WindowSizeMulValue, UIScale.ihY() * UInGameValue::WindowSizeMulValue}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue}});

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

	for (int i = 0; i < UInGameValue::CoinCountRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUIComponent));
		CoinCountRenderer.push_back(Renderer);
		CoinCountRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = CoinCountRenderer[i]->GetImage()->GetScale();
		CoinCountRenderer[i]->SetTransform({ {UInGameValue::UIScoreRendInitXPos + UInGameValue::UISpacingBetRends * (10 + i), UInGameValue::UIRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
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
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUIComponent));
		StageInfoRenderer.push_back(Renderer);
		StageInfoRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = StageInfoRenderer[i]->GetImage()->GetScale();
		StageInfoRenderer[i]->SetTransform({ {UInGameValue::UIStageInfoRendInitXPos + UInGameValue::UISpacingBetRends * (i * 2), UInGameValue::UIRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
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


	for (int i = 0; i < UInGameValue::StageInfoRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUIComponent));
		StageInfoCenterRenderer.push_back(Renderer);
		StageInfoCenterRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = StageInfoCenterRenderer[i]->GetImage()->GetScale();
		StageInfoCenterRenderer[i]->SetTransform({ {UInGameValue::UIStageInfoCRendInitXPos + UInGameValue::UISpacingBetRends * (i * 2), UInGameValue::UIStageInfoCRendInitYPos}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue} });
		StageInfoCenterRenderer[i]->CameraEffectOff();
		StageInfoCenterRenderer[i]->CreateAnimation("0", "Numbers.png", 0, 0, false);
		StageInfoCenterRenderer[i]->CreateAnimation("1", "Numbers.png", 1, 1, false);
		StageInfoCenterRenderer[i]->CreateAnimation("2", "Numbers.png", 2, 2, false);
		StageInfoCenterRenderer[i]->CreateAnimation("3", "Numbers.png", 3, 3, false);
		StageInfoCenterRenderer[i]->CreateAnimation("4", "Numbers.png", 4, 4, false);
		StageInfoCenterRenderer[i]->CreateAnimation("5", "Numbers.png", 5, 5, false);
		StageInfoCenterRenderer[i]->CreateAnimation("6", "Numbers.png", 6, 6, false);
		StageInfoCenterRenderer[i]->CreateAnimation("7", "Numbers.png", 7, 7, false);
		StageInfoCenterRenderer[i]->CreateAnimation("8", "Numbers.png", 8, 8, false);
		StageInfoCenterRenderer[i]->CreateAnimation("9", "Numbers.png", 9, 9, false);
	}
	
	NumberToAnimation(IntroScore, 6, ScoreRenderer);
	NumberToAnimation(IntroAmountOfCoins, 2, CoinCountRenderer);
	for (int i = 0; i < UInGameValue::StageInfoRendererSize; i++)
	{
		StageInfoCenterRenderer[i]->ChangeAnimation(IntroStageInfo[i]);
		StageInfoRenderer[i]->ChangeAnimation(IntroStageInfo[i]);
	}
}

void ALevelIntro::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	if (IsPlaying)
	{
		RenderingTime -= _DeltaTime;
	}

	if (0.0f >= RenderingTime)
	{
		IsPlaying = false;
		RenderingTime = 2.0f;
		//UIRenderer->ActiveOff();
		AllRenderersActiveOff();
		GetWorld()->SetTimeScale(EActorType::UI, 1.0f);
		GetWorld()->SetTimeScale(EActorType::Player, 1.0f);
		GetWorld()->SetTimeScale(EActorType::Monster, 1.0f);
	}
}

void ALevelIntro::NumberToAnimation(int _PrintNumber, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer)
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
