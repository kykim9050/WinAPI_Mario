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

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::ItemsImageXValue * UInGameValue::WindowSizeMulValue, ItemScale.iY() / UInGameValue::ItemsImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Mushroom", "Items.png", 0, 0, 0.1f, true);
	Renderer->ChangeAnimation("Mushroom");

	BodyCollision = CreateCollision(ECollisionOrder::Item);
	//BodyCollision->SetTransform({ { 0, 0}, { UInGameValue::MushroomCollisionScaleX, UInGameValue::MushroomCollisionScaleX} });
	BodyCollision->SetTransform({ { 0, 0}, { 32, 32} });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void AMushroom::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}


void AMushroom::FirstInit(float _Deltatime)
{
	InitPos = GetActorLocation();
	StateChange(EActorState::Idle);
}

void AMushroom::IdleStart()
{
	AItemUnit::IdleStart();

	BodyCollision->ActiveOff();
	Renderer->ActiveOff();
}

void AMushroom::AppearStart()
{
	Renderer->ActiveOn();
}

void AMushroom::MoveStart()
{
	BodyCollision->ActiveOn();
}





void AMushroom::Idle(float _DeltaTime)
{

}


void AMushroom::Appear(float _DeltaTime)
{
	if (GetActorLocation().Y < 400.0f)
	{
		SetActorLocation({GetActorLocation().X, GetActorLocation().Y });
		StateChange(EActorState::Move);
	}

	AddActorLocation(FVector::Up * 100.0f * _DeltaTime);
}

void AMushroom::Move(float _DeltaTime)
{
	AddActorLocation(FVector::Right * 100.0f * _DeltaTime);
}