#include "CastleBridge.h"
#include "BridgeBlock.h"

bool ACastleBridge::IsTagBridgeFlag = false;

ACastleBridge::ACastleBridge()
{

}

ACastleBridge::~ACastleBridge()
{
}

void ACastleBridge::BeginPlay()
{
	AStructureUnit::BeginPlay();

	for (int i = 0; i < UInGameValue::BridgeBlockAmount; i++)
	{
		ABridgeBlock* BridgeBlock = GetWorld()->SpawnActor<ABridgeBlock>(static_cast<int>(EActorType::Block));
		BridgeBlock->SetActorLocation({ UInGameValue::BridgeStartXPos + UInGameValue::BTBDistance * i,  UInGameValue::BridgeStartYPos });
		BridgeBlocks.push_front(BridgeBlock);
	}

	BridgeChainRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	BridgeChainRenderer->SetImage("CastleItems.png");
	FVector CastleItemsScale = BridgeChainRenderer->GetImage()->GetScale();
	BridgeChainRenderer->SetTransform({ { UInGameValue::BTBDistance * (UInGameValue::BridgeBlockAmount - 1), -UInGameValue::BTBDistance}, {CastleItemsScale.iX() / UInGameValue::CastleItemsImgXValue * UInGameValue::WindowSizeMulValue, CastleItemsScale.iY() / UInGameValue::CastleItemsImgYValue * UInGameValue::WindowSizeMulValue} });
	BridgeChainRenderer->CreateAnimation("BridgeChain", "CastleItems.png", 0, 0, 0.1f, false);
	BridgeChainRenderer->ChangeAnimation("BridgeChain");

	BridgeFlagRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	BridgeFlagRenderer->SetImage("CastleItems.png");
	BridgeFlagRenderer->SetTransform({ { UInGameValue::BTBDistance * UInGameValue::BridgeBlockAmount, -(UInGameValue::BTBDistance * 2)}, {CastleItemsScale.iX() / UInGameValue::CastleItemsImgXValue * UInGameValue::WindowSizeMulValue, CastleItemsScale.iY() / UInGameValue::CastleItemsImgYValue * UInGameValue::WindowSizeMulValue} });
	BridgeFlagRenderer->CreateAnimation("BridgeFlag", "CastleItems.png", { 8,8,8,8,9,10,9 }, 0.15f, true);
	BridgeFlagRenderer->ChangeAnimation("BridgeFlag");

	BridgeFlagCollision = CreateCollision(ECollisionOrder::CastleEndFlag);
	BridgeFlagCollision->SetTransform({ { UInGameValue::BTBDistance * UInGameValue::BridgeBlockAmount, -(UInGameValue::BTBDistance * 2)}, {UInGameValue::CastleEndFlagXScale, UInGameValue::CastleEndFlagYScale } });
	BridgeFlagCollision->SetColType(ECollisionType::Rect);
}

void ACastleBridge::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void ACastleBridge::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr != BridgeFlagCollision && true == BridgeFlagCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BridgeFlagCollision->ActiveOff();
		BridgeFlagRenderer->ActiveOff();

		GetWorld()->SetOtherTimeScale(EActorType::Structure, 0.0f);
		GetWorld()->SetTimeScale(EActorType::Monster, 1.0f);
		//GetWorld()->SetTimeScale(EActorType::Block, 1.0f);

		StateChange(EActorState::FallDown);
		TagBridgeFlag();
		return;
	}
}

void ACastleBridge::FallDown(float _DeltaTime)
{
	static int EndStep = 0;
	static float DelayTime = 0.5f;

	switch (EndStep)
	{
	case 0:
	{
		DelayTime -= _DeltaTime;

		if (0.0f >= DelayTime)
		{
			if (nullptr == BridgeChainRenderer)
			{
				MsgBoxAssert("BridgeChainRenderer가 nullptr 입니다.");
				break;
			}

			BridgeChainRenderer->ActiveOff();
			EndStep = 1;
			DelayTime = 0.2f + DelayTime;
			break;
		}

		break;
	}
	case 1:
	{
		// 끝에 Bridge 블럭부터 하나씩 사라진다. 0.2초간격	
		DelayTime -= _DeltaTime;

		std::list<ABridgeBlock*>::iterator StartIter = BridgeBlocks.begin();
		std::list<ABridgeBlock*>::iterator EndIter = BridgeBlocks.end();

		if (StartIter == EndIter)
		{
			DelayTime = 0.2f + DelayTime;
			EndStep = 2;
			break;
		}

		if (0.0f >= DelayTime)
		{
			DelayTime = 0.3f + DelayTime;
			ABridgeBlock* Block = *StartIter;

			if (nullptr == Block)
			{
				MsgBoxAssert("제거할 대상 Block이 nullptr 입니다.");
				return;
			}

			Block->GetRenderer()->ActiveOff();
			Block->GetBodyCollision()->ActiveOff();
			StartIter = BridgeBlocks.erase(StartIter);
			break;
		}
		break;
	}
	case 2:
	{

		break;
	}
	default:
		break;
	}

	

	//switch (EndStep)
	//{
	//case 0:	// 첫 번째 단계 : 깃대를 잡고 내려감
	//{
	//	DelayTime -= _DeltaTime;

	//	if (0.0f >= DelayTime)
	//	{
	//		// 지정 시간이 지나면 Player 반대편으로 도는 애니메이션 취하기
	//		SetActorLocation({ GetActorLocation().X + BodyCollision->GetTransform().GetScale().X + static_cast<float>(UInGameValue::EndFlagCollisionXScale), GetActorLocation().Y });
	//		Renderer->ChangeAnimation(ChangeAnimationName("StopClimbDownAndTurnRight", true));
	//		DelayTime = 1.0f;
	//		EndStep = 1;
	//		break;
	//	}

	//	Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

	//	if (UInGameValue::CollisionColor == Color)
	//	{
	//		// Player 아래에 충돌체 만나면 내려가기 멈추고 시간이 다될때까지 대기
	//		Renderer->ChangeAnimation(ChangeAnimationName("StopClimbDown", true));
	//		break;
	//	}

	//	AddActorLocation(FVector::Down * 400.0f * _DeltaTime);
	//	break;
	//}
	//case 1:	// 도는 애니메이션 취하고 일정 시간 동안 대기하는 기능
	//{
	//	DelayTime -= _DeltaTime;

	//	if (0.0f >= DelayTime)
	//	{
	//		// 깃발을 잡고 내려간 후에 걸어서 성문 입구로 걸어가기 시작 (자동 - 조작 안먹힘)
	//		Renderer->ChangeAnimation(ChangeAnimationName("Move_Right", true));
	//		SetJumpZero();
	//		DelayTime = 0.0f;
	//		EndStep = 2;
	//		break;
	//	}

	//	break;
	//}
	//case 2: // 성문에 충돌할때까지 계속해서 오른쪽으로 걷기
	//{
	//	if (IsReachingCastleGate)
	//	{
	//		// Stage종료
	//		StateChange(EActorState::ReachStageEnd);
	//		EndStep = -1;
	//		IsReachingCastleGate = false;
	//	}

	//	HorizonVelocityVector = FVector::Right * 150.0f;

	//	ResultMovementUpdate(_DeltaTime);
	//	break;
	//}
	//default:
	//	break;
	//}
}

void ACastleBridge::FallDownStart()
{
	BridgeFlagRenderer->Destroy();
	BridgeFlagCollision->Destroy();
}