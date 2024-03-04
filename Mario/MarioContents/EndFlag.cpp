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

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->Destroy();
		Player->ReachToStageEnd();
		return;
	}
}