#include "Mushroom.h"

AMushroom::AMushroom()
{
}

AMushroom::~AMushroom()
{
}

void AMushroom::BeginPlay()
{
	AItemUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Items.png");

	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::ItemsImageXValue, ItemScale.iY() / UInGameValue::ItemsImageYValue} });
	Renderer->CreateAnimation("Mushroom", "Items.png", 0, 0, 0.1f, true);
	Renderer->ChangeAnimation("Mushroom");

	StateChange(EActorState::Idle);
}

void AMushroom::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}

void AMushroom::IdleStart()
{
	AItemUnit::IdleStart();
	int a = 0;
}

void AMushroom::Idle(float _DeltaTime)
{
	int a = 0;
}

