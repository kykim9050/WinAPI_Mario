#pragma once
#include "EnumClass.h"
#include "InGameValue.h"
#include "StateUnit.h"

class UImageRenderer;

// Ό³Έν :
class AItemUnit : public UStateUnit
{
	friend class ABlockUnit;
public:
	// constrcuter destructer
	AItemUnit();
	~AItemUnit();

	// delete Function
	AItemUnit(const AItemUnit& _Other) = delete;
	AItemUnit(AItemUnit&& _Other) noexcept = delete;
	AItemUnit& operator=(const AItemUnit& _Other) = delete;
	AItemUnit& operator=(AItemUnit&& _Other) noexcept = delete;

	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	
	void IdleStart() override;
	void MoveStart() override;
	void ReleaseStart();


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	float CoinRenderingTime = 0.7f;
	bool RenderingEnd = false;
};

