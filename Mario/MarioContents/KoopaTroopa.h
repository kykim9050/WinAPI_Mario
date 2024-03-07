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

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void GetFirstHit(float _DeltaTime) override;
	void GetSecondHit(float _DeltaTime) override;
	void GetMonsterHit(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime);
	void ResultMovementUpdate(float _DeltaTime) override;

	void CollisionCheck() override;

	void IdleStart() override;
	void MoveStart() override;
	void GetFirstHitStart() override;
	void GetSecondHitStart() override;
	void GetHitFromMonsterStart() override;
	void GetHitStart() override;
	void GetMonsterHitStart() override;

	void SetDirAfterCollision(const FVector _MyFVector, const FVector _OtherFVector);

private:

};

