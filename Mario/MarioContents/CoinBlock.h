#pragma once
#include "BlockUnit.h"

// Ό³Έν :
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

private:
	AItemUnit* Item = nullptr;
	EItemType ItemType = EItemType::None;
};

