#pragma once
#include "StateUnit.h"
#include "PlayerMario.h"
#include "MainPlayer.h"

class  ATextUnit;
// Ό³Έν :
class AMonsterUnit : public UStateUnit, public UMainPlayer
{
public:
	// constrcuter destructer
	AMonsterUnit();
	~AMonsterUnit();

	// delete Function
	AMonsterUnit(const AMonsterUnit& _Other) = delete;
	AMonsterUnit(AMonsterUnit&& _Other) noexcept = delete;
	AMonsterUnit& operator=(const AMonsterUnit& _Other) = delete;
	AMonsterUnit& operator=(AMonsterUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;
	void CollisionStateChange(ECollisionState _CollisionState) override;
	void DeadCollisionCheck() override;
	void CalGravityVelocityVector(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime) override;
	void ResultMovementUpdate(float _DeltaTime) override;

	virtual void FirstInit(float _DeltaTime) {};
	virtual void Idle(float _DeltaTime) {};
	virtual void Move(float _DeltaTime) {};
	virtual void Fire(float _DeltaTime) {};
	virtual void GetBlockHit(float _DeltaTime) {};
	virtual void GetFirstHit(float _DeltaTime) {};
	virtual void GetSecondHit(float _DeltaTime) {};
	virtual void GetMonsterHit(float _DeltaTime) {};
	virtual void FallDown(float _DeltaTime) {};
	virtual void IdleStart() {};
	virtual void MoveStart() {};
	virtual void FireStart() {};
	virtual void GetFirstHitStart() {};
	virtual void GetSecondHitStart() {};
	virtual void GetHitFromPlayerStart() {};
	virtual void GetHitFromMonsterStart() {};
	virtual void FallDownStart() {};
	virtual void GetHitStart() {};
	virtual void GetMonsterHitStart() {};
	virtual void GetBlockHitStart() {};


	void ScoreImgOperator(FVector _InitPos, int _Score, float _DestoryTime = 0.5f);
	bool PlayerBulletHitCheck();

	bool IsMonsterDead() const
	{
		return MonsterDead;
	}

	FVector ActorMoveDir = FVector::Left;
	UCollision* FootCollision = nullptr;
	ATextUnit* Score = nullptr;
	
	int GetMonsterHitScore() const
	{
		return MonsterHitScore;
	}

private:
	void SetMonsterDead()
	{
		MonsterDead = true;
	}

	bool MonsterDead = false;
	int MonsterHitScore = 500;
};

