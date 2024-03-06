#pragma once
#include "DebugLevel.h"
#include "CoinBlock.h"


class ABackGroundMap;
class UCollisionMap;
class APlayerMario;
class AUI;
// 설명 :
class UStageLevel : public UDebugLevel
{
public:
	// constrcuter destructer
	UStageLevel();
	~UStageLevel();

	// delete Function
	UStageLevel(const UStageLevel& _Other) = delete;
	UStageLevel(UStageLevel&& _Other) noexcept = delete;
	UStageLevel& operator=(const UStageLevel& _Other) = delete;
	UStageLevel& operator=(UStageLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;


	template<typename EnumType1, typename EnumType2>
	ACoinBlock* SpawnCoinBlock(EnumType1 _ActorType = 0, EnumType2 _ItemType = 0)
	{
		ACoinBlock* CoinBlock = SpawnCoinBlock(static_cast<int>(_ActorType), _ItemType);
		return CoinBlock;
	}

	template<typename EnumType>
	ACoinBlock* SpawnCoinBlock(int _Order, EnumType _ItemType)
	{
		ACoinBlock* CoinBlock = SpawnActor< ACoinBlock>(_Order);
		
		if (nullptr == CoinBlock)
		{
			MsgBoxAssert("CoinBlock이 생성되지 않았습니다.");
			return nullptr;
		}

		CoinBlock->SetItemType(_ItemType);
		return CoinBlock;
	}

	ABackGroundMap* Map = nullptr;
	UCollisionMap* ColMap = nullptr;
	APlayerMario* Mario = nullptr;
	AUI* PlayerUI = nullptr;


private:
};

