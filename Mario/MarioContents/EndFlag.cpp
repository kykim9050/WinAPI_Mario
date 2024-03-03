#include "EndFlag.h"

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

	
	//BodyCollision = CreateCollision(ECollisionOrder::Monster);
	//BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::GoombaBodyCollisionScaleX, UInGameValue::GoombaBodyCollisionScaleY } });
	//BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	//BodyCollision->SetColType(ECollisionType::Rect);

	//SetActorState(EActorState::Move);
}

void AEndFlag::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}
