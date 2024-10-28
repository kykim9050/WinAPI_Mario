#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"

// ���� :
class AKoopaTroopa : public UStateUnit
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

	void StateUpdate(float _DeltaTime) override;

	void Move(float _DeltaTime) override;

	void ResultMovementUpdate(float _DeltaTime) override;

	void CollisionUpdate(float _DeltaTime) override;

	void CollisionStateChange(ECollisionState _CollisionState) override;

	void GetHitStart() override;

	// StateUnit�� virtual�� ������ ���~
	void CollisionCheck();

	void StateChange(EActorState _ActorState) override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void GetFirstHitStart();
	void GetSecondHitStart();

	void GetFirstHit(float _DeltaTime);
	void GetSecondHit(float _DeltaTime);


private:
	bool KillPlayer = false;
};

