#include "BrickBlock.h"

ABrickBlock::ABrickBlock()
{
}

ABrickBlock::~ABrickBlock()
{
}

void ABrickBlock::BeginPlay()
{
	ABlockUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	Renderer->SetImage("BrickBlock.png");

	FVector BrickBlockScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {BrickBlockScale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, BrickBlockScale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("BrickBlock_Init", "BrickBlock.png", 0, 0, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_EmptyHit", "BrickBlock.png", 1, 1, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_Hit", "BrickBlock.png", 3, 3, 0.1f, true);
	Renderer->CreateAnimation("BrickBlock_AfterHit", "BrickBlock.png", 4, 4, 0.1f, true);

	DebrisRenderer1 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisRenderer2 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisRenderer3 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisRenderer4 = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisRenderer1->SetImage("BrickBlock.png");
	DebrisRenderer2->SetImage("BrickBlock.png");
	DebrisRenderer3->SetImage("BrickBlock.png");
	DebrisRenderer4->SetImage("BrickBlock.png");

	FVector DebrisBlock1Scale = DebrisRenderer1->GetImage()->GetScale();
	FVector DebrisBlock2Scale = DebrisRenderer2->GetImage()->GetScale();
	FVector DebrisBlock3Scale = DebrisRenderer3->GetImage()->GetScale();
	FVector DebrisBlock4Scale = DebrisRenderer4->GetImage()->GetScale();

	DebrisRenderer1->SetTransform({ {0,0}, {DebrisBlock1Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock1Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisRenderer2->SetTransform({ {0,0}, {DebrisBlock2Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock2Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisRenderer3->SetTransform({ {0,0}, {DebrisBlock3Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock3Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisRenderer4->SetTransform({ {0,0}, {DebrisBlock4Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock4Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });

	DebrisRenderer1->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	DebrisRenderer2->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	DebrisRenderer3->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	DebrisRenderer4->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);


	SetActorState(EActorState::FirstInit);
}

void ABrickBlock::Tick(float _DeltaTime)
{
	ABlockUnit::Tick(_DeltaTime);
}

void ABrickBlock::CollisionCheck()
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
			return;
		}
	}

	CollisionStateChange(ECollisionState::None);
}


void ABrickBlock::IdleStart()
{
	ABlockUnit::IdleStart();
	Renderer->ChangeAnimation("BrickBlock_Init");
}

void ABrickBlock::MoveStart()
{
	ABlockUnit::MoveStart();

	Renderer->ChangeAnimation("BrickBlock_EmptyHit");
}


void ABrickBlock::Move(float _DeltaTime)
{
	ABlockUnit::Move(_DeltaTime);

	if (GetActorLocation().Y >= InitPos.Y)
	{
		GravityVelocityVector = FVector::Zero;
		JumpVelocityVector = FVector::Zero;
		SetActorLocation(InitPos);
		StateChange(EActorState::Idle);
	}
}

void ABrickBlock::Debris(float _DeltaTime)
{
	ABlockUnit::Debris(_DeltaTime);

}

void ABrickBlock::DebrisStart()
{
	ABlockUnit::DebrisStart();

	TopCollision->ActiveOff();
	SideCollision->ActiveOff();
	BodyCollision->ActiveOff();
	Renderer->ChangeAnimation("BrickBlock_Debris");

	DebrisRenderer1->ChangeAnimation("BrickBlock_Debris");
	DebrisRenderer2->ChangeAnimation("BrickBlock_Debris");
	DebrisRenderer3->ChangeAnimation("BrickBlock_Debris");
	DebrisRenderer4->ChangeAnimation("BrickBlock_Debris");
}







