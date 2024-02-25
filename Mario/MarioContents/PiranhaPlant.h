#pragma once
#include "MonsterUnit.h"

// Ό³Έν :
class APiranhaPlant : public UMonsterUnit
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

	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;

	void IdleStart();
	void MoveStart();

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override ;
	void ResultMovementUpdate(float _DeltaTime) override;
	
private:
	float IdleDelayTime = 1.0f;
};

