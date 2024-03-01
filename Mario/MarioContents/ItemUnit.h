#pragma once
#include "EnumClass.h"
#include "InGameValue.h"
#include "StateUnit.h"

class UImageRenderer;

// Ό³Έν :
class AItemUnit : public UStateUnit
{
public:
	// constrcuter destructer
	AItemUnit();
	~AItemUnit();

	// delete Function
	AItemUnit(const AItemUnit& _Other) = delete;
	AItemUnit(AItemUnit&& _Other) noexcept = delete;
	AItemUnit& operator=(const AItemUnit& _Other) = delete;
	AItemUnit& operator=(AItemUnit&& _Other) noexcept = delete;

	void StateUpdate(float _DeltaTime);
	void StateChange(EActorState _ActorState);

	virtual void CollisionCheck() {}
	virtual void CollisionStateChange(ECollisionState _CollisionState);

	virtual void FirstInit(float _DeltaTime) {}
	virtual void Idle(float _DeltaTime) {}
	virtual void Move(float _DeltaTime) {}
	virtual void Appear(float _DeltaTime) {}


	virtual void IdleStart() {}
	virtual void AppearStart() {}
	virtual void MoveStart() {}
	virtual void ReleaseStart() {}
	

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	FVector InitPos = FVector::Zero;
	bool IsAte = false;
private:


};

