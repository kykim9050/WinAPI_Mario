#include "LevelIntro.h"
#include "PlayerScoreManager.h"
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

	IntroLife = UPlayerScoreManager::GetInst().GetPlayerLife();
	IntroAmountOfCoins = UPlayerScoreManager::GetInst().GetAmountOfCoins();
	IntroScore = UPlayerScoreManager::GetInst().GetPlayerScore();
	IntroStageInfo = UPlayerScoreManager::GetInst().GetStageInfo();

	UIRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::IntroUI));
	UIRenderer->SetImage("LevelIntro.png");
	FVector UIScale = UIRenderer->GetImage()->GetScale();
	UIRenderer->SetTransform({ {UIScale.ihX() * UInGameValue::WindowSizeMulValue, UIScale.ihY() * UInGameValue::WindowSizeMulValue}, {UIScale.iX() * UInGameValue::WindowSizeMulValue, UIScale.iY() * UInGameValue::WindowSizeMulValue}});

	
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
		UIRenderer->ActiveOff();
		GetWorld()->SetTimeScale(EActorType::UI, 1.0f);
		GetWorld()->SetTimeScale(EActorType::Player, 1.0f);
	}
}

