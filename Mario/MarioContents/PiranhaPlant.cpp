#include "PiranhaPlant.h"

APiranhaPlant::APiranhaPlant()
{
	JumpVelocityVector = FVector::Up * 50.0f;
	Life = 1;
}

APiranhaPlant::~APiranhaPlant()
{
}

void APiranhaPlant::BeginPlay()
{
	UMonsterUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Monster));
	Renderer->SetImage("PiranhaPlant.png");

	FVector PiranhaPlantScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {PiranhaPlantScale.iX() / UInGameValue::PiranhaPlantImageXValue * UInGameValue::WindowSizeMulValue, PiranhaPlantScale.iY() / UInGameValue::PiranhaPlantImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("PiranhaPlant_Move", "PiranhaPlant.png", 0, 1, 0.2f, true);
	Renderer->ChangeAnimation("PiranhaPlant_Move");

	BodyCollision = CreateCollision(ECollisionOrder::Monster);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::PiranhaPlantBodyCollisionScaleX, UInGameValue::PiranhaPlantBodyCollisionScaleY} });
	BodyCollision->SetPosition({ 0, -(BodyCollision->GetTransform().GetScale().ihY()) });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::Move);
}

void APiranhaPlant::Tick(float _DeltaTime)
{
	UMonsterUnit::Tick(_DeltaTime);


	StateUpdate(_DeltaTime);
}

void APiranhaPlant::StateUpdate(float _DeltaTime)
{
	switch (ActorState)
	{
	case EActorState::Idle:
		//Idle(_DeltaTime);
		break;
	case EActorState::Move:
		Move(_DeltaTime);
		break;
	default:
		break;
	}
}

void APiranhaPlant::Move(float _DeltaTime)
{
	ResultMovementUpdate(_DeltaTime);
	//if(GetActorLocation().Y < )
	//CalHorizonVelocityVector(_DeltaTime);
	//HorizonVelocityVector = ActorMoveDir * 50.0f;
}

void APiranhaPlant::ResultMovementUpdate(float _DeltaTime)
{
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}