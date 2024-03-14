#include "Mushroom.h"
#include "PlayerMario.h"

AMushroom::AMushroom()
{
	SetScore(1000);
	ActorDir = EActorDir::Right;
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

	BodyCollision = CreateCollision(ECollisionOrder::Mushroom);
	BodyCollision->SetTransform({ { 0, 0}, { UInGameValue::MushroomCollisionScaleX, UInGameValue::MushroomCollisionScaleY} });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void AMushroom::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}

void AMushroom::FirstInit(float _DeltaTime)
{
	AItemUnit::FirstInit(_DeltaTime);

	BodyCollision->ActiveOff();
	Renderer->ActiveOff();

	StateChange(EActorState::Idle);
}


void AMushroom::AppearStart()
{
	USoundManager::GetInst().EffectSoundPlay("UpgradeItemAppear.wav");
}

void AMushroom::MoveStart()
{
	BodyCollision->ActiveOn();
}


void AMushroom::Appear(float _DeltaTime)
{
	if (GetActorLocation().Y < InitPos.Y - (UInGameValue::BlockCollisionScaleY / 2) - (UInGameValue::MushroomCollisionScaleY / 2))
	{
		SetActorLocation({ GetActorLocation().X, GetActorLocation().Y });
		StateChange(EActorState::Move);
	}

	AddActorLocation(FVector::Up * 60.0f * _DeltaTime);
}

void AMushroom::Move(float _DeltaTime)
{
	if (GetActorLocation().X + GetBodyCollision()->GetTransform().GetScale().hX() < GetWorld()->GetCameraPos().X)
	{
		Renderer->ActiveOff();
		BodyCollision->ActiveOff();
		StateChange(EActorState::Idle);
		return;
	}

	ResultMovementUpdate(_DeltaTime);
}

void AMushroom::CalGravityVelocityVector(float _DeltaTime)
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY() + GetBodyCollision()->GetTransform().GetScale().ihY(), UInGameValue::CollisionColor);

	if (UInGameValue::CollisionColor == Color || true == GetBodyCollision()->CollisionCheck(ECollisionOrder::BlockTop, Result))
	{
		GravityVelocityVector = FVector::Zero;
		return;
	}

	GravityVelocityVector += FVector::Down * GravityVel * _DeltaTime;
}

void AMushroom::CalHorizonVelocityVector(float _DeltaTime)
{
	FVector CheckPos = GetActorLocation();

	switch (ActorDir)
	{
	case EActorDir::Right:
		CheckPos.X += GetBodyCollision()->GetTransform().iRight();
		break;
	case EActorDir::Left:
		CheckPos.X -= GetBodyCollision()->GetTransform().iLeft();
		break;
	default:
		break;
	}

	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(CheckPos.iX(), CheckPos.iY(), UInGameValue::CollisionColor);

	if (Color == UInGameValue::CollisionColor)
	{
		switch (ActorDir)
		{
		case EActorDir::Right:
		{
			ActorDir = EActorDir::Left;
			MoveDir = FVector::Left;
			break;
		}
		case EActorDir::Left:
		{
			ActorDir = EActorDir::Right;
			MoveDir = FVector::Right;
			break;
		}
		default:
			break;
		}
	}

	HorizonVelocityVector = MoveDir * MushroomSpeed;
}

void AMushroom::ResultMovementUpdate(float _DeltaTime)
{
	CalHorizonVelocityVector(_DeltaTime);
	CalGravityVelocityVector(_DeltaTime);
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}



void AMushroom::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		GetPlayer()->EattingMushroom();
		CollisionStateChange(ECollisionState::GetHit);
		return;
	}
}

void AMushroom::GetHitStart()
{
	AItemUnit::GetHitStart();

	ScoreImgOperator(GetActorLocation(), GetScore());
	GiveScore(GetPlayer());
}