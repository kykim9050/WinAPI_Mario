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

	BodyCollision = CreateCollision(ECollisionOrder::MonsterBullet);
	BodyCollision->SetTransform({ { 0,0 }, { UInGameValue::KoopaBulletXColScale, UInGameValue::KoopaBulletYColScale } });
	BodyCollision->SetColType(ECollisionType::Rect);

	Renderer->ActiveOff();
	BodyCollision->ActiveOff();

	SetActorState(EActorState::FirstInit);
}

void AKoopaBullet::Tick(float _DeltaTime)
{
	ABulletUnit::Tick(_DeltaTime);
}

void AKoopaBullet::FirstInit(float _DeltaTime)
{
	ABulletUnit::FirstInit(_DeltaTime);

	if (IsBulletFire())
	{
		StateChange(EActorState::Move);
		return;
	}
}

void AKoopaBullet::MoveStart()
{
	ABulletUnit::MoveStart();

	USoundManager::GetInst().EffectSoundPlay("KoopaFlame.mp3");

	Renderer->ActiveOn();
	BodyCollision->ActiveOn();

	if (FVector::Right.iX() == GetBulletDir().iX())
	{
		Renderer->ChangeAnimation("Firing_Right");
	}
	else if (FVector::Left.iX() == GetBulletDir().iX())
	{
		Renderer->ChangeAnimation("Firing_Left");
	}

	HorizonVelocityVector = GetBulletDir() * 200.0f;
	Destroy(10.0f);
}

void AKoopaBullet::Move(float _DeltaTime)
{
	ABulletUnit::Move(_DeltaTime);

	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}