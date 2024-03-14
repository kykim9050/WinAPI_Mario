#include "MarioBullet.h"

AMarioBullet::AMarioBullet()
{
}

AMarioBullet::~AMarioBullet()
{
}

void AMarioBullet::BeginPlay()
{
	ABulletUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Bullet));
	Renderer->SetImage("FireBall.png");
	FVector FireBallScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {FireBallScale.iX() / UInGameValue::FireBallImageXValue * UInGameValue::WindowSizeMulValue, FireBallScale.iY() / UInGameValue::FireBallImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("FiringBullet", "FireBall.png", 0, 3, 0.1f, true);
	Renderer->CreateAnimation("FireBallDestroy", "FireBall.png", 4, 6, 0.1f, false);
	Renderer->ChangeAnimation("FiringBullet");

	//Renderer->CreateAnimation("Firing_Right", "KoopaFire_Right.png", 0, 1, 0.1f, true);

	//BodyCollision = CreateCollision(ECollisionOrder::MonsterBullet);
	//BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBulletXColScale, UInGameValue::KoopaBulletYColScale } });
	//BodyCollision->SetColType(ECollisionType::Rect);

	//Renderer->ActiveOff();
	//BodyCollision->ActiveOff();

	//SetActorState(EActorState::FirstInit);
}

void AMarioBullet::Tick(float _DeltaTime)
{
	ABulletUnit::Tick(_DeltaTime);
}

