#pragma once
#include "DebugLevel.h"
#include "CoinBlock.h"

// Ό³Έν :
class UCreateLevel : public UDebugLevel
{
public:
	// constrcuter destructer
	UCreateLevel();
	~UCreateLevel();

	// delete Function
	UCreateLevel(const UCreateLevel& _Other) = delete;
	UCreateLevel(UCreateLevel&& _Other) noexcept = delete;
	UCreateLevel& operator=(const UCreateLevel& _Other) = delete;
	UCreateLevel& operator=(UCreateLevel&& _Other) noexcept = delete;

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
		CoinBlock->SetItemType(_ItemType);
		return CoinBlock;
	}

private:

};

