#include "EndFlag.h"
#include "PlayerMario.h"

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

		//FlagRenderer->AddPosition({ FVector::Down * _DeltaTime * 500.0f });
}

void AEndFlag::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->ActiveOff();
		GetPlayer()->ReachToStageEnd();
		StateChange(EActorState::ReachingEndFlag);
		return;
	}
}

void AEndFlag::ReachingEndFlag(float _DeltaTime)
{
	int a = 0;
}

void AEndFlag::ReachingEndFlagStart()
{
	int a = 0;
}
