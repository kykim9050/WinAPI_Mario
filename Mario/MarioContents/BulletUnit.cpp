#include "BulletUnit.h"

ABulletUnit::ABulletUnit()
{
}

ABulletUnit::~ABulletUnit()
{
}

void ABulletUnit::BeginPlay()
{
	UStateUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Bullet));
	Renderer->SetImage("KoopaFire_Left.png");

	FVector KoopaFireScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {KoopaFireScale.iX() / UInGameValue::KoopaFireImgXValue * UInGameValue::WindowSizeMulValue, KoopaFireScale.iY() / UInGameValue::KoopaFireImgYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Firing_Left", "KoopaFire_Left.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Firing_Right", "KoopaFire_Right.png", 0, 1, 0.1f, true);
	Renderer->ChangeAnimation("Firing_Left");
}

void ABulletUnit::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}