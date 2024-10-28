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

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("EndFlag.png");

	FVector EndFlagScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {EndFlagScale.iX() * UInGameValue::WindowSizeMulValue, EndFlagScale.iY() * UInGameValue::WindowSizeMulValue} });

	
	BodyCollision = CreateCollision(ECollisionOrder::EndFlagLine);
	BodyCollision->SetTransform({ { 0,0 }, { 5 * UInGameValue::WindowSizeMulValue, 500 * UInGameValue::WindowSizeMulValue} });
	//BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	//SetActorState(EActorState::Move);
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
		MsgBoxAssert("�÷��̾ �������� �ʽ��ϴ�.");
	}

	if (nullptr != BodyCollision && true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->Destroy();
		//Player->EattingMushroom();
		//CollisionStateChange(ECollisionState::GetHit);
		return;
	}
}