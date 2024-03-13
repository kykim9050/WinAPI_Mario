#include "FireFlower.h"
#include "PlayerMario.h"

AFireFlower::AFireFlower()
{
	SetScore(1000);
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

	BodyCollision = CreateCollision(ECollisionOrder::FireFlower);
	BodyCollision->SetTransform({ { 0, 0}, { UInGameValue::FireFlowerCollisionScaleX, UInGameValue::FireFlowerCollisionScaleY} });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void AFireFlower::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}

void AFireFlower::FirstInit(float _DeltaTime)
{
	AItemUnit::FirstInit(_DeltaTime);

	BodyCollision->ActiveOff();
	Renderer->ActiveOff();
}

void AFireFlower::Appear(float _DeltaTime)
{
	if (GetActorLocation().Y < InitPos.Y - (UInGameValue::BlockCollisionScaleY / 2) - (UInGameValue::FireFlowerCollisionScaleY / 2))
	{
		SetActorLocation({ GetActorLocation().X, GetActorLocation().Y });
		StateChange(EActorState::Idle);
	}

	AddActorLocation(FVector::Up * 60.0f * _DeltaTime);
}

void AFireFlower::AppearStart()
{
	USoundManager::GetInst().EffectSoundPlay("UpgradeItemAppear.wav");
}

void AFireFlower::IdleStart()
{
	BodyCollision->ActiveOn();
}

void AFireFlower::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		GetPlayer()->EattingFireFlower();
		CollisionStateChange(ECollisionState::GetHit);
		return;
	}
}

void AFireFlower::GetHitStart()
{
	AItemUnit::GetHitStart();

	ScoreImgOperator(GetActorLocation(), GetScore());
	GiveScore(GetPlayer());
}

