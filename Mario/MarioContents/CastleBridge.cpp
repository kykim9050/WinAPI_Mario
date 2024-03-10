#include "CastleBridge.h"
#include "BridgeBlock.h"

bool ACastleBridge::IsTagBridgeFlag = false;
bool ACastleBridge::BridgeDissapear = false;

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
	BridgeFlagCollision->SetTransform({ { UInGameValue::BTBDistance * UInGameValue::BridgeBlockAmount, -(UInGameValue::BTBDistance * 2)}, {static_cast<int>(UInGameValue::CastleEndFlagXScale / 2), UInGameValue::CastleEndFlagYScale } });
	BridgeFlagCollision->SetColType(ECollisionType::Rect);
}

void ACastleBridge::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}

void ACastleBridge::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr == BridgeFlagCollision)
	{
		return;
	}

	if (nullptr != BridgeFlagCollision && true == BridgeFlagCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BridgeFlagCollision->ActiveOff();
		BridgeFlagRenderer->ActiveOff();

		GetWorld()->SetOtherTimeScale(EActorType::Structure, 0.0f);
		GetWorld()->SetTimeScale(EActorType::Monster, 1.0f);

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

			BridgeChainRenderer->Destroy();
			BridgeChainRenderer = nullptr;
			EndStep = 1;
			DelayTime = 0.5f + DelayTime;
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
			DelayTime = 0.5f + DelayTime;
			EndStep = 2;
			break;
		}

		if (0.0f >= DelayTime)
		{
			DelayTime = 0.1f + DelayTime;
			ABridgeBlock* Block = *StartIter;

			if (nullptr == Block)
			{
				MsgBoxAssert("제거할 대상 Block이 nullptr 입니다.");
				return;
			}

			Block->Destroy();
			Block = nullptr;
			StartIter = BridgeBlocks.erase(StartIter);
			break;
		}
		break;
	}
	case 2:
	{
		EndStep = 3;
		SetBridgeDissapear();
		break;
	}
	default:
		break;
	}
}

void ACastleBridge::FallDownStart()
{
	BridgeFlagRenderer->Destroy();
	BridgeFlagRenderer = nullptr;
	BridgeFlagCollision->Destroy();
	BridgeFlagCollision = nullptr;
}