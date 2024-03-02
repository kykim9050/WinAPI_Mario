#include "CoinBlock.h"
#include "BlockCoin.h"
#include "Mushroom.h"
#include "FireFlower.h"

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

	//Item = GetWorld()->SpawnActor< AMushroom>(static_cast<int>(EActorType::Item));
	Item = GetWorld()->SpawnActor< AFireFlower>(static_cast<int>(EActorType::Item));
}

void ACoinBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

void ACoinBlock::FirstInit(float _Deltatime)
{
	ABlockUnit::FirstInit(_Deltatime);
	Item->SetActorLocation({ InitPos.X, InitPos.Y});
}

void ACoinBlock::IdleStart()
{
	ABlockUnit::IdleStart();
	Renderer->ChangeAnimation("CoinBlock_Init");
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

	Item->GetRenderer()->ActiveOn();
	Renderer->ChangeAnimation("CoinBlock_AfterHit");
}


void ACoinBlock::CollisionCheck()
{
	ABlockUnit::CollisionCheck();

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	// Block의 바닥과 Player의 충돌일 때
	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		const FTransform& PlayerColTrans = Player->GetBodyCollision()->GetActorBaseTransform();
		const FTransform& BlockColTrans = BodyCollision->GetActorBaseTransform();


		if (PlayerColTrans.GetPosition().X < BlockColTrans.Right() && PlayerColTrans.GetPosition().X > BlockColTrans.Left() && PlayerColTrans.GetPosition().Y < BlockColTrans.Bottom())
		{
			//UEngineDebug::OutPutDebugText("Occur Block Bot Collision");
			Player->HitBlockBottom();

			CollisionStateChange(ECollisionState::GetHit);

			if (Item->IsDestroy())
			{
				return;
			}
			Item->StateChange(EActorState::Appear);
			return;
		}
	}

	CollisionStateChange(ECollisionState::None);
}