#include "KoopaBullet.h"

AKoopaBullet::AKoopaBullet()
{
}

AKoopaBullet::~AKoopaBullet()
{
}

void AKoopaBullet::BeginPlay()
{
	ABulletUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Bullet));
	Renderer->SetImage("KoopaFire_Left.png");

	FVector KoopaFireScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {KoopaFireScale.iX() / UInGameValue::KoopaFireImgXValue * UInGameValue::WindowSizeMulValue, KoopaFireScale.iY() / UInGameValue::KoopaFireImgYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Firing_Left", "KoopaFire_Left.png", 0, 1, 0.1f, true);
	Renderer->CreateAnimation("Firing_Right", "KoopaFire_Right.png", 0, 1, 0.1f, true);
	Renderer->ChangeAnimation("Firing_Left");

	BodyCollision = CreateCollision(ECollisionOrder::MonsterBullet);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBulletXColScale, UInGameValue::KoopaBulletYColScale } });
	BodyCollision->SetColType(ECollisionType::Rect);
}

void AKoopaBullet::Tick(float _DeltaTime)
{
	ABulletUnit::Tick(_DeltaTime);
}


