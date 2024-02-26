#pragma once
#include "MonsterUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"

// Ό³Έν :
class AKoopaTroopa : public AMonsterUnit
{
public:
	// constrcuter destructer
	AKoopaTroopa();
	~AKoopaTroopa();

	// delete Function
	AKoopaTroopa(const AKoopaTroopa& _Other) = delete;
	AKoopaTroopa(AKoopaTroopa&& _Other) noexcept = delete;
	AKoopaTroopa& operator=(const AKoopaTroopa& _Other) = delete;
	AKoopaTroopa& operator=(AKoopaTroopa&& _Other) noexcept = delete;

	

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void GetFirstHit(float _DeltaTime);
	void GetSecondHit(float _DeltaTime);
	void GetMonsterHit(float _DeltaTime);
	void CalHorizonVelocityVector(float _DeltaTime);
	void ResultMovementUpdate(float _DeltaTime) override;

	//void CollisionUpdate(float _DeltaTime) override;
	void CollisionStateChange(ECollisionState _CollisionState) override;
	void CollisionCheck() override;

	void IdleStart();
	void MoveStart();
	void GetFirstHitStart();
	void GetSecondHitStart();
	void GetHitFromMonsterStart();
	void GetHitStart() override;
	void GetMonsterHitStart();

	void SetDirAfterCollision(const FVector _MyFVector, const FVector _OtherFVector);

private:

};

