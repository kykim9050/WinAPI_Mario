#pragma once
#include "MonsterUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"


// Ό³Έν :
class AGoomba : public UMonsterUnit
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

	

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;

	void GetHitStart() override;
	void GetHitFromPlayerStart();

	void Move(float _DeltaTime) override;
	void GetMonsterHit(float _DeltaTime);
	void ResultMovementUpdate(float _DeltaTime) override;

	void CollisionCheck() override;
	void CollisionUpdate(float _DeltaTime) override;
	void CollisionStateChange(ECollisionState _CollisionState) override;
	void GetMonsterHitStart();
	void GetHitFromMonsterStart();

private:
	bool KillPlayer = false;
};

