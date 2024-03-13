#include "Castle.h"
#include "PlayerMario.h"

ACastle::ACastle()
{
}

ACastle::~ACastle()
{
}

void ACastle::BeginPlay()
{
	AStructureUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	Renderer->SetImage("MiniCastle.png");
	FVector CastleScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {CastleScale.iX() * UInGameValue::WindowSizeMulValue, CastleScale.iY() * UInGameValue::WindowSizeMulValue} });

	
	FlagRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundSubStructure));
	FlagRenderer->SetImage("flags.png");
	FVector FlagScale = FlagRenderer->GetImage()->GetScale();
	FlagRenderer->SetTransform({ {ActorBaseCastleFlagXPos, ActorBaseCastleFlagYPos}, {FlagScale.iX() / UInGameValue::flagsImgXValue * UInGameValue::WindowSizeMulValue, FlagScale.iY() * UInGameValue::flagsImgYValue * UInGameValue::WindowSizeMulValue} });
	FlagRenderer->CreateAnimation("CastleFlag", "flags.png", 1, 1, 0.1f, false);
	FlagRenderer->ChangeAnimation("CastleFlag");

	BodyCollision = CreateCollision(ECollisionOrder::CastleGate);
	BodyCollision->SetTransform({ { 16,0 }, { UInGameValue::CastleGateCollisionXScale, UInGameValue::CastleGateCollisionYScale} });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void ACastle::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void ACastle::CollisionCheck()
{
	AStructureUnit::CollisionCheck();

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->ActiveOff();
		GetPlayer()->ReachToCastleGate();
		return;
	}
}
