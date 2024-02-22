#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"


// Ό³Έν :
class AGoomba : public UStateUnit
{
public:
	// constrcuter destructer
	AGoomba();
	~AGoomba();

	// delete Function
	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

	void StateUpdate(float _DeltaTime) override;

	void Move(float _DeltaTime) override;

	void ResultMovementUpdate(float _DeltaTime) override;

	void CollisionUpdate(float _DeltaTime) override;

	void CollisionStateChange(ECollisionState _CollisionState) override;

	void GetHitStart() override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool KillPlayer = false;
};

