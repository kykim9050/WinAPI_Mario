#pragma once
#include "StructureUnit.h"


class ABridgeBlock;
// Ό³Έν :
class ACastleBridge : public AStructureUnit
{
public:
	// constrcuter destructer
	ACastleBridge();
	~ACastleBridge();

	// delete Function
	ACastleBridge(const ACastleBridge& _Other) = delete;
	ACastleBridge(ACastleBridge&& _Other) noexcept = delete;
	ACastleBridge& operator=(const ACastleBridge& _Other) = delete;
	ACastleBridge& operator=(ACastleBridge&& _Other) noexcept = delete;

	std::list<ABridgeBlock*> GetBridgeBlocks() const
	{
		return BridgeBlocks;
	}

	static const bool PlayerIsTagBridgeFlag()
	{
		return IsTagBridgeFlag;
	}

	static const bool IsBridgeDissapear()
	{
		return BridgeDissapear;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck() override;

	void FallDown(float _DeltaTime) override;
	void FallDownStart() override;

private:
	std::list<ABridgeBlock*> BridgeBlocks = std::list<ABridgeBlock*>();

	

	UImageRenderer* BridgeChainRenderer = nullptr;
	UImageRenderer* BridgeFlagRenderer = nullptr;
	UCollision* BridgeFlagCollision = nullptr;

	static bool IsTagBridgeFlag;
	static void TagBridgeFlag()
	{
		IsTagBridgeFlag = true;
	}

	static bool BridgeDissapear;
	static void SetBridgeDissapear()
	{
		BridgeDissapear = true;
	}
};

