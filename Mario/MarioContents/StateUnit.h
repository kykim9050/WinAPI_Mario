#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"
#include "PlayerInfoManager.h"
#include "SoundManager.h"

// 설명 :
class UStateUnit : public AActor
{
public:
	// constrcuter destructer
	UStateUnit();
	virtual ~UStateUnit();

	// delete Function
	UStateUnit(const UStateUnit& _Other) = delete;
	UStateUnit(UStateUnit&& _Other) noexcept = delete;
	UStateUnit& operator=(const UStateUnit& _Other) = delete;
	UStateUnit& operator=(UStateUnit&& _Other) noexcept = delete;

	UCollision* GetBodyCollision() const
	{
		return BodyCollision;
	}

	UImageRenderer* GetRenderer() const
	{
		return Renderer;
	}

	const void SetJumpZero()
	{
		JumpVelocityVector = FVector::Zero;
	}

	const void SetGravityZero()
	{
		GravityVelocityVector = FVector::Zero;
	}

	const void SetGravityRatio(float _RatioValue)
	{
		GravityRatio = _RatioValue;
	}

	const void SetSpeedZero()
	{
		HorizonVelocityVector = FVector::Zero;
	}

	void GiveScore(UStateUnit* _Other, int _Score)
	{
		if (nullptr == _Other)
		{
			MsgBoxAssert("대상 오브젝트가 존재하지 않습니다.");
		}

		_Other->AddScore(_Score);
	}

	void GiveScore(UStateUnit* _Other)
	{
		if (nullptr == _Other)
		{
			MsgBoxAssert("대상 오브젝트가 존재하지 않습니다.");
		}

		int MyScore = GetScore();

		_Other->AddScore(MyScore);
	}

	int GetScore() const
	{
		return Score;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void IdleStart() {};
	virtual void MoveStart() {};
	virtual void JumpStart() {};
	virtual void GetHitStart() {};

	virtual void Idle(float _DeltaTime) {};
	virtual void Move(float _DeltaTime) {};
	virtual void Jump(float _DeltaTime) {};
	virtual void GetHit(float _DeltaTime) {};

	virtual void StateChange(EActorState _ActorState) {};
	virtual void StateUpdate(float _DeltaTime) {};
	void SetActorState(const EActorState _State)
	{
		ActorState = _State;
	}
	void SetActorDir(const EActorDir _Dir)
	{
		ActorDir = _Dir;
	}
	
	
	virtual void CollisionUpdate(float _DeltaTime);
	virtual void CollisionStateChange(ECollisionState _CollisionState) {};
	virtual void CollisionCheck() {};
	virtual void DeadCollisionCheck() {};
	void SetCollisionState(ECollisionState _CollisionState)
	{
		ActorCollisionState = _CollisionState;
	}

	virtual void ResultMovementUpdate(float _DeltaTime) {};
	virtual void AddHorizonVelocityVector(const FVector& _DirDelta) {};
	virtual void ApplyMovement(float _DeltaTime) {};
	virtual void CalHorizonVelocityVector(float _DeltaTime) {};
	virtual void CalJumpVelocityVector(float _DeltaTime) {};

	virtual void CalGravityVelocityVector(float _DeltaTime) {};
	void CalTotalVelocityVector(float _DeltaTime);

	

	void AddScore(const int _Score)
	{
		Score += _Score;
		UPlayerInfoManager::GetInst().AddPlayerScore(_Score);
	}

	void SetScore(int _Value)
	{
		Score = _Value;
	}


	EActorState ActorState = EActorState::None;
	EActorDir ActorDir = EActorDir::Left;
	ECollisionState ActorCollisionState = ECollisionState::None;

	FVector HorizonVelocityVector = FVector::Zero;
	FVector GravityVelocityVector = FVector::Zero;
	FVector GravityAccVector = FVector::Down * 1500.0f;
	FVector TotalVelocityVector = FVector::Zero;
	FVector JumpVelocityVector = FVector::Zero;

	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	std::string CurAnimationName = "None";

	float GravityRatio = 1.0f;

	int Life = 1;

private:
	int Score = 0;
};

