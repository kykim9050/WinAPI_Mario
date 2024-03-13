#include "EndFlag.h"
#include "PlayerMario.h"
#include "TextUnit.h"

AEndFlag::AEndFlag()
{
}

AEndFlag::~AEndFlag()
{
}

void AEndFlag::BeginPlay()
{
	AStructureUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	Renderer->SetImage("EndFlag.png");
	FVector EndFlagScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {EndFlagScale.iX() * UInGameValue::WindowSizeMulValue, EndFlagScale.iY() * UInGameValue::WindowSizeMulValue} });

	FlagRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundSubStructure));
	FlagRenderer->SetImage("flags.png");
	FVector FlagScale = FlagRenderer->GetImage()->GetScale();
	FlagRenderer->SetTransform({ {ActorBaseFlagXPos, ActorBaseFlagYPos}, {FlagScale.iX() / UInGameValue::flagsImgXValue * UInGameValue::WindowSizeMulValue, FlagScale.iY() * UInGameValue::flagsImgYValue * UInGameValue::WindowSizeMulValue} });
	FlagRenderer->CreateAnimation("Flag", "flags.png", 0, 0, 0.1f, false);
	FlagRenderer->ChangeAnimation("Flag");

	BodyCollision = CreateCollision(ECollisionOrder::EndFlagLine);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::EndFlagCollisionXScale, UInGameValue::EndFlagCollisionYScale} });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void AEndFlag::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void AEndFlag::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		if (GetPlayer()->GetActorLocation().Y < GetActorLocation().Y - 150.0f)
		{
			SetScore(5000);
		}
		else if (GetPlayer()->GetActorLocation().Y < GetActorLocation().Y)
		{
			SetScore(2000);
		}
		else
		{
			SetScore(400);
		}

		USoundManager::GetInst().BGMSoundStop();
		BodyCollision->ActiveOff();
		GetPlayer()->ReachToStageEnd();
		StateChange(EActorState::ReachingEndFlag);
		return;
	}
}

void AEndFlag::ReachingEndFlag(float _DeltaTime)
{
	if (Renderer->GetTransform().iBottom() - 76 <= FlagRenderer->GetPosition().iY())
	{
		StateChange(EActorState::Idle);
		Score->StopRising();
		GiveScore(GetPlayer(), GetScore());
		return;
	}

	FlagRenderer->AddPosition({ FVector::Down * _DeltaTime * 200.0f });
}

void AEndFlag::ReachingEndFlagStart()
{
	// 스코어 랜더러 관련 클래스 생성
	Score = GetWorld()->SpawnActor<ATextUnit>(static_cast<int>(EActorType::ScoreImg));
	// 스코어 랜더러가 시작될 위치 지정
	Score->SetLocation({ GetActorLocation().iX() + 36, BodyCollision->GetTransform().iBottom() - 76});
	// 스코어 랜더러에서 출력하고자 하는 점수 출력
	Score->SetScoreAnimation(GetScore());
	Score->SetSpeed(400.0f);
}
