#include "Koopa.h"

AKoopa::AKoopa()
{
}

AKoopa::~AKoopa()
{
}

void AKoopa::BeginPlay()
{
	AMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("Koopa_Left.png");
	FVector KoopaScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {KoopaScale.iX() / UInGameValue::KoopaImgXValue * UInGameValue::WindowSizeMulValue, KoopaScale.iY() / UInGameValue::KoopaImgYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Koopa_LeftMove", "Koopa_Left.png", 0, 1, 0.3f, true);
	Renderer->CreateAnimation("Koopa_RightMove", "Koopa_Right.png", 0, 1, 0.3f, true);

	Renderer->ChangeAnimation("Koopa_LeftMove");


	//BodyCollision = CreateCollision(ECollisionOrder::Monster);
	//BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaTroopaBodyCollisionScaleX, UInGameValue::KoopaTroopaBodyCollisionScaleY} });
	//BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	//BodyCollision->SetColType(ECollisionType::Rect);

	//SetActorState(EActorState::Idle);

}

void AKoopa::Tick(float _DeltaTime)
{
	AMonsterUnit::Tick(_DeltaTime);
}