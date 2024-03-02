#include "FireFlower.h"

AFireFlower::AFireFlower()
{
}

AFireFlower::~AFireFlower()
{
}

void AFireFlower::BeginPlay()
{
	AItemUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Items.png");


	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::ItemsImageXValue * UInGameValue::WindowSizeMulValue, ItemScale.iY() / UInGameValue::ItemsImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("FireFlower", "Items.png", 2, 5, 0.15f, true);
	Renderer->ChangeAnimation("FireFlower");

	//BodyCollision = CreateCollision(ECollisionOrder::Mushroom);
	//BodyCollision->SetTransform({ { 0, 0}, { UInGameValue::MushroomCollisionScaleX, UInGameValue::MushroomCollisionScaleX} });
	//BodyCollision->SetColType(ECollisionType::Rect);

	//SetActorState(EActorState::FirstInit);
}

void AFireFlower::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}
