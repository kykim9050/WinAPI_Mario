#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"

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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void IdleStart() {}
	virtual void MoveStart() {}
	virtual void JumpStart() {}
	virtual void GetHitStart() {}

	virtual void Idle(float _DeltaTime) {}
	virtual void Move(float _DeltaTime) {}
	virtual void Jump(float _DeltaTime) {}
	virtual void GetHit(float _DeltaTime) {}

	virtual void StateChange(EActorState _ActorState) {}
	virtual void StateUpdate(float _DeltaTime) {}
	void SetActorState(const EActorState _State)
	{
		ActorState = _State;
	}
	void SetActorDir(const EActorDir _Dir)
	{
		ActorDir = _Dir;
	}
	
	virtual void CollisionUpdate(float _DeltaTime) {}
	virtual void CollisionStateChange(ECollisionState _CollisionState) {}
	void SetCollisionState(ECollisionState _CollisionState)
	{
		ActorCollisionState = _CollisionState;
	}

	virtual void ResultMovementUpdate(float _DeltaTime) {}
	virtual void AddHorizonVelocityVector(const FVector& _DirDelta) {}
	virtual void ApplyMovement(float _DeltaTime) {}
	virtual void CalHorizonVelocityVector(float _DeltaTime) {}
	virtual void CalJumpVelocityVector(float _DeltaTime) {}

	void CalGravityVelocityVector(float _DeltaTime);
	void CalTotalVelocityVector(float _DeltaTime);

	/// <summary>
	/// 방향 정보가 적용된 애니메이션 이름으로 수정하는 함수
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName);




	EActorState ActorState = EActorState::None;
	EActorDir ActorDir = EActorDir::Right;
	ECollisionState ActorCollisionState = ECollisionState::None;

	FVector HorizonVelocityVector = FVector::Zero;
	FVector GravityVelocityVector = FVector::Zero;
	FVector GravityAccVector = FVector::Down * 2000.0f;
	FVector TotalVelocityVector = FVector::Zero;
	FVector JumpVelocityVector = FVector::Zero;

	int Life;

	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	std::string CurAnimationName = "None";


private:
};

