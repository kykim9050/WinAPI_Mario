#include "LevelIntro.h"
#include "PlayerInfoManager.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "SoundManager.h"

ALevelIntro::ALevelIntro()
{
}

ALevelIntro::~ALevelIntro()
{
}

void ALevelIntro::BeginPlay()
{
	AUIBaseInfo::BeginPlay();

	IntroLife = UPlayerInfoManager::GetInst().GetPlayerLife();

	UIRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUI));
	UIRenderer->SetImage("LevelIntro.png");
	FVector UIScale = UIRenderer->GetImage()->GetScale();
	UIRenderer->SetTransform({ {UIScale.ihX() * UInGameValue::WindowSizeMulValue, UIScale.ihY() * UInGameValue::WindowSizeMulValue}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue}});


	for (int i = 0; i < UInGameValue::LifeRendererSize; i++)
	{
		UImageRenderer* Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUIComponent));
		LifeRenderer.push_back(Renderer);
		LifeRenderer[i]->SetImage("Numbers.png");
		FVector UINumberScale = LifeRenderer[i]->GetImage()->GetScale();
		LifeRenderer[i]->SetTransform({ {UInGameValue::LifeRendInitXPos * UInGameValue::WindowSizeMulValue, UInGameValue::LifeRendInitYPos * UInGameValue::WindowSizeMulValue}, {UINumberScale.iX() / UInGameValue::NumberImageXValue * UInGameValue::WindowSizeMulValue , UINumberScale.iY() / UInGameValue::NumberImageYValue * UInGameValue::WindowSizeMulValue}});
		LifeRenderer[i]->CameraEffectOff();
		LifeRenderer[i]->CreateAnimation("0", "Numbers.png", 0, 0, false);
		LifeRenderer[i]->CreateAnimation("1", "Numbers.png", 1, 1, false);
		LifeRenderer[i]->CreateAnimation("2", "Numbers.png", 2, 2, false);
		LifeRenderer[i]->CreateAnimation("3", "Numbers.png", 3, 3, false);
		LifeRenderer[i]->CreateAnimation("4", "Numbers.png", 4, 4, false);
		LifeRenderer[i]->CreateAnimation("5", "Numbers.png", 5, 5, false);
		LifeRenderer[i]->CreateAnimation("6", "Numbers.png", 6, 6, false);
		LifeRenderer[i]->CreateAnimation("7", "Numbers.png", 7, 7, false);
		LifeRenderer[i]->CreateAnimation("8", "Numbers.png", 8, 8, false);
		LifeRenderer[i]->CreateAnimation("9", "Numbers.png", 9, 9, false);
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
	
	NumberToAnimation(IntroLife, 1, LifeRenderer);
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
	AUIBaseInfo::Tick(_DeltaTime);

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
		USoundManager::GetInst().BGMSoundPlay(GetWorld()->GetName());
	}
}