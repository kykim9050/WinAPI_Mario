#pragma once
#include "BlockUnit.h"

// ���� :
class ACoinBlock : public ABlockUnit
{
public:
	// constrcuter destructer
	ACoinBlock();
	~ACoinBlock();

	// delete Function
	ACoinBlock(const ACoinBlock& _Other) = delete;
	ACoinBlock(ACoinBlock&& _Other) noexcept = delete;
	ACoinBlock& operator=(const ACoinBlock& _Other) = delete;
	ACoinBlock& operator=(ACoinBlock&& _Other) noexcept = delete;

	void SetItemType(EItemType _Type)
	{
		ItemType = _Type;
	}

	void FixingBlock()
	{
		FixedBlock = true;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FirstInit(float _Deltatime) override;
	void IdleStart() override;
	void MoveStart() override;
	void GetHitStart() override;

	void Move(float _DeltaTime) override;
	void FixedStart() override;

	void CollisionCheck() override;

	void Wait(float _DeltaTime) override;

private:
	AItemUnit* Item = nullptr;
	EItemType ItemType = EItemType::None;
	static bool ItemIsMushroom;
	bool FixedBlock = false;
};

