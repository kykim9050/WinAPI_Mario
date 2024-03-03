#include "StructureUnit.h"

AStructureUnit::AStructureUnit()
{
}

AStructureUnit::~AStructureUnit()
{
}

void AStructureUnit::BeginPlay()
{
	UStateUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("EndFlag.png");
	
	FVector EndFlagScale = Renderer->GetImage()->GetScale();

	//Renderer->SetTransform({ {0,0}, {GoombaScale.iX() / UInGameValue::GoombaImageXValue * UInGameValue::WindowSizeMulValue, GoombaScale.iY() / UInGameValue::GoombaImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->SetTransform({ {0,0}, {EndFlagScale.iX() * UInGameValue::WindowSizeMulValue, EndFlagScale.iY() * UInGameValue::WindowSizeMulValue} });
	//Renderer->CreateAnimation("Goomba_Move", "Goomba.png", 0, 1, 0.2f, true);
	//Renderer->CreateAnimation("Goomba_Dead", "Goomba.png", 2, 2, 0.1f, true);
	//Renderer->ChangeAnimation("Goomba_Move");


	//BodyCollision = CreateCollision(ECollisionOrder::Monster);
	//BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::GoombaBodyCollisionScaleX, UInGameValue::GoombaBodyCollisionScaleY } });
	//BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	//BodyCollision->SetColType(ECollisionType::Rect);

	//SetActorState(EActorState::Move);
}

void AStructureUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}