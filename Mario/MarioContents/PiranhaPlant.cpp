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
}

void APiranhaPlant::Tick(float _DeltaTime)
{
	UMonsterUnit::Tick(_DeltaTime);
}