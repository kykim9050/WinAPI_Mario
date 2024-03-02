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

	for (int i = 0; i < 4/*UInGameValue::DebrisBlockNum*/; i++)
	{
		ADebrisBlock* NewBlock = GetWorld()->SpawnActor< ADebrisBlock>(static_cast<int>(EActorType::Block));
		DebrisBlocks.push_back(NewBlock);
	}

	DebrisBlocks[0]->Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisBlocks[1]->Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisBlocks[2]->Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisBlocks[3]->Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Block));
	DebrisBlocks[0]->Renderer->SetImage("BrickBlock.png");
	DebrisBlocks[1]->Renderer->SetImage("BrickBlock.png");
	DebrisBlocks[2]->Renderer->SetImage("BrickBlock.png");
	DebrisBlocks[3]->Renderer->SetImage("BrickBlock.png");

	FVector DebrisBlock1Scale = DebrisBlocks[0]->Renderer->GetImage()->GetScale();
	FVector DebrisBlock2Scale = DebrisBlocks[1]->Renderer->GetImage()->GetScale();
	FVector DebrisBlock3Scale = DebrisBlocks[2]->Renderer->GetImage()->GetScale();
	FVector DebrisBlock4Scale = DebrisBlocks[3]->Renderer->GetImage()->GetScale();

	DebrisBlocks[0]->Renderer->SetTransform({ {0,0}, {DebrisBlock1Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock1Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisBlocks[1]->Renderer->SetTransform({ {0,0}, {DebrisBlock2Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock2Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisBlocks[2]->Renderer->SetTransform({ {0,0}, {DebrisBlock3Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock3Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
	DebrisBlocks[3]->Renderer->SetTransform({ {0,0}, {DebrisBlock4Scale.iX() / UInGameValue::BrickBlockImageXValue * UInGameValue::WindowSizeMulValue, DebrisBlock4Scale.iY() / UInGameValue::BrickBlockImageYValue * UInGameValue::WindowSizeMulValue} });
				  
	DebrisBlocks[0]->Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	DebrisBlocks[1]->Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	DebrisBlocks[2]->Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);
	DebrisBlocks[3]->Renderer->CreateAnimation("BrickBlock_Debris", "BrickBlock.png", 2, 2, 0.1f, true);

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

	Debrisingtime -= _DeltaTime;

	if (0.0f >= Debrisingtime)
	{

		Debrisingtime = 1.0f;
		StateChange(EActorState::Release);
	}

	GravityVelocityVector += GravityAccVector * _DeltaTime;
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);

	UEngineDebug::OutPutDebugText("X :" + std::to_string(GetActorLocation().X));
	UEngineDebug::OutPutDebugText("Y :" + std::to_string(GetActorLocation().Y));

	/*DebrisBlocks[0]->Renderer->SetPosition({ (FVector::Left + FVector::Up) * 100.0f });
	DebrisBlocks[1]->Renderer->SetPosition({ (FVector::Right + FVector::Up) * 100.0f });
	DebrisBlocks[2]->Renderer->SetPosition({ (FVector::Left + FVector::Down) * 100.0f });
	DebrisBlocks[3]->Renderer->SetPosition({ (FVector::Right + FVector::Down) * 100.0f});*/
	
	
}

void ABrickBlock::DebrisStart()
{
	ABlockUnit::DebrisStart();

	TopCollision->ActiveOff();
	SideCollision->ActiveOff();
	BodyCollision->ActiveOff();
	Renderer->ActiveOff();
	//Renderer->ChangeAnimation("BrickBlock_Debris");
	JumpVelocityVector = FVector::Up * 600.0f;

	DebrisBlocks[0]->Renderer->ChangeAnimation("BrickBlock_Debris");
	DebrisBlocks[1]->Renderer->ChangeAnimation("BrickBlock_Debris");
	DebrisBlocks[2]->Renderer->ChangeAnimation("BrickBlock_Debris");
	DebrisBlocks[3]->Renderer->ChangeAnimation("BrickBlock_Debris");
}

void ABrickBlock::FirstInit(float _Deltatime)
{
	ABlockUnit::FirstInit(_Deltatime);

	for (int i = 0; i < 4/*UInGameValue::DebrisBlockNum*/; i++)
	{
		DebrisBlocks[i]->SetActorLocation({ InitPos.X, InitPos.Y });
	}

}