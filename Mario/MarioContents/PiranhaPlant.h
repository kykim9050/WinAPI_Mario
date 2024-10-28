#pragma once
#include "MonsterUnit.h"

// ���� :
class APiranhaPlant : public AMonsterUnit
{
public:
	// constrcuter destructer
	APiranhaPlant();
	~APiranhaPlant();

	// delete Function
	APiranhaPlant(const APiranhaPlant& _Other) = delete;
	APiranhaPlant(APiranhaPlant&& _Other) noexcept = delete;
	APiranhaPlant& operator=(const APiranhaPlant& _Other) = delete;
	APiranhaPlant& operator=(APiranhaPlant&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck() override;

	void IdleStart() override;
	void MoveStart() override;

	void FirstInit(float _Deltatime);
	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override ;
	void ResultMovementUpdate(float _DeltaTime) override;
	
private:
	float IdleDelayTime = 1.0f;
	FVector InitPos = FVector::Zero;
};

