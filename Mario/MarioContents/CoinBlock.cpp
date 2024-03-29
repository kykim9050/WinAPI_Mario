#include "CoinBlock.h"
#include "BlockCoin.h"
#include "Mushroom.h"
#include "FireFlower.h"

bool ACoinBlock::ItemIsMushroom = true;

ACoinBlock::ACoinBlock()
{
}

ACoinBlock::~ACoinBlock()
{
}

void ACoinBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	Renderer->SetImage("CoinBlock.png");

	FVector CoinBlockScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {CoinBlockScale.iX() / UInGameValue::CoinBlockImageXValue * UInGameValue::WindowSizeMulValue, CoinBlockScale.iY() / UInGameValue::CoinBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("CoinBlock_Init", "CoinBlock.png", { 0, 0, 0, 0, 1, 2, 1 }, 0.15f, true);
	Renderer->CreateAnimation("CoinBlock_Hit", "CoinBlock.png", 3, 3, 0.1f, true);
	Renderer->CreateAnimation("CoinBlock_AfterHit", "CoinBlock.png", 4, 4, 0.1f, true);

	SetActorState(EActorState::FirstInit);
}

void ACoinBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

void ACoinBlock::FirstInit(float _Deltatime)
{
	ABlockUnit::FirstInit(_Deltatime);

	Renderer->ChangeAnimation("CoinBlock_Init");

	SetActorState(EActorState::Wait);
}


void ACoinBlock::IdleStart()
{
	ABlockUnit::IdleStart();
	Renderer->ChangeAnimation("CoinBlock_Init");

	switch (ItemType)
	{
	case EItemType::Coin:
	{
		Item = GetWorld()->SpawnActor< ABlockCoin>(static_cast<int>(EActorType::Item));
		break;
	}
	case EItemType::Item:
	{
		if (ItemIsMushroom)
		{
			Item = GetWorld()->SpawnActor< AMushroom>(static_cast<int>(EActorType::Item));
		}
		else
		{
			Item = GetWorld()->SpawnActor< AFireFlower>(static_cast<int>(EActorType::Item));
		}
		break;
	}
	default:
		break;
	}

	if (nullptr == Item)
	{
		MsgBoxAssert("Item이 생성되지 않았습니다.");
	}

	Item->SetActorLocation({ InitPos.X, InitPos.Y});

}

void ACoinBlock::MoveStart()
{
	ABlockUnit::MoveStart();

	Renderer->ChangeAnimation("CoinBlock_Hit");
}

void ACoinBlock::Move(float _DeltaTime)
{
	ABlockUnit::Move(_DeltaTime);

	if (GetActorLocation().Y >= InitPos.Y)
	{
		GravityVelocityVector = FVector::Zero;
		JumpVelocityVector = FVector::Zero;
		SetActorLocation(InitPos);
		StateChange(EActorState::Fixed);
	}
}

void ACoinBlock::FixedStart()
{
	ABlockUnit::FixedStart();

	FixedBlock = true;
	Item->GetRenderer()->ActiveOn();
	Renderer->ChangeAnimation("CoinBlock_AfterHit");
}


void ACoinBlock::CollisionCheck()
{
	ABlockUnit::CollisionCheck();

	std::vector<UCollision*> Result = std::vector<UCollision*>();


	// Block의 바닥과 Player의 충돌일 때
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		const FTransform& PlayerColTrans = GetPlayer()->GetBodyCollision()->GetActorBaseTransform();
		const FTransform& BlockColTrans = BodyCollision->GetActorBaseTransform();
		float PlayerTop = GetPlayer()->GetBodyCollision()->GetActorBaseTransform().Top();
		float BlockBotColTop = BodyCollision->GetActorBaseTransform().Top();
		float OffsetYValue = BodyCollision->GetActorBaseTransform().GetScale().hY();

		if (PlayerColTrans.GetPosition().X < BlockColTrans.Right()
			&& PlayerColTrans.GetPosition().X > BlockColTrans.Left()
			&& PlayerTop < BlockBotColTop + OffsetYValue + OffsetYValue / 2)
		{
			GetPlayer()->HitBlockBottom();

			if (true == FixedBlock)
			{
				return;
			}

			CollisionStateChange(ECollisionState::GetHit);
			Item->StateChange(EActorState::Appear);
			return;
		}
	}

	if (true == PlayerSideColCheck())
	{
		return;
	}

	CollisionStateChange(ECollisionState::None);
}

void ACoinBlock::GetHitStart()
{
	ABlockUnit::GetHitStart();

	if (EActorState::Fixed == ActorState)
	{
		return;
	}

	EMarioType type = GetPlayer()->GetPlayerType();


	switch (type)
	{
	case EMarioType::Small:
	case EMarioType::Big:
	case EMarioType::Fire:
		StateChange(EActorState::Move);
		break;
	default:
		break;
	}
}

void ACoinBlock::Wait(float _DeltaTime)
{
	ABlockUnit::Wait(_DeltaTime);

	if (50.0f > (InitPos.X - GetPlayer()->GetActorLocation().X))
	{
		EMarioType type = GetPlayer()->GetPlayerType();

		switch (type)
		{
		case EMarioType::Small:
		{
			// 버섯이 나오게 설정
			ItemIsMushroom = true;
			break;
		}
		case EMarioType::Big:
		case EMarioType::Fire:
		{
			//불꽃이 나오게 설정
			ItemIsMushroom = false;
			break;
		}
		default:
			break;
		}


		StateChange(EActorState::Idle);
	}
}