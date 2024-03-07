#pragma once
#include "MonsterUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"


// Ό³Έν :
class AGoomba : public AMonsterUnit
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

	//void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;

	void GetHitStart() override;
	void GetHitFromPlayerStart();

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void GetMonsterHit(float _DeltaTime);
	void CalHorizonVelocityVector(float _DeltaTime) override;
	void ResultMovementUpdate(float _DeltaTime) override;

	void CollisionCheck() override;
	void CollisionStateChange(ECollisionState _CollisionState) override;
	void GetMonsterHitStart();
	void GetHitFromMonsterStart();


private:
	
};

