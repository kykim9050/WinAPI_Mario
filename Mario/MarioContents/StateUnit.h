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
	//virtual void CollisionJumpStart() {}
	//virtual void FreeMoveStart() {}
	//virtual void ReverseMoveStart() {}
	virtual void GetHitStart() {}

	virtual void StateChange(EActorState _ActorState) {}
	virtual void StateUpdate(float _DeltaTime) {}
	
	void SetActorDir(const EActorDir _Dir)
	{
		ActorDir = _Dir;
	}

	//bool DirCheck();

	//bool IsReverseMove();

	/*static APlayerMario* GetMainPlayer()
	{
		return MainPlayer;
	}*/

	virtual void CollisionUpdate(float _DeltaTime) {}
	virtual void CollisionStateChange(ECollisionState _CollisionState) {}
	void SetCollisionState(ECollisionState _CollisionState)
	{
		ActorCollisionState = _CollisionState;
	}
	
	//void CameraPosUpdate(FVector _Player, FVector _MovePos);
	
	/// <summary>
	/// 방향 정보가 적용된 애니메이션 이름으로 수정하는 함수
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName)
	{
		std::string Dir = "";
		CurAnimationName = _MainName;

		switch (ActorDir)
		{
		case EActorDir::Left:
			Dir = "_Left";
			break;
		case EActorDir::Right:
			Dir = "_Right";
			break;
		default:
			break;
		}

		return CurAnimationName + Dir;
	}

	//void FreeMove(float _DeltaTime);
	//void CameraMove(float _DeltaTime);
	virtual void Idle(float _DeltaTime) {}
	virtual void Move(float _DeltaTime) {}
	virtual void Jump(float _DeltaTime) {}
	//void CollisionJump(float _DeltaTime);
	//void ReverseMove(float _DeltaTime);
	virtual void GetHit(float _DeltaTime) {}


	virtual void ResultMovementUpdate(float _DeltaTime) {}

	virtual void AddHorizonVelocityVector(const FVector& _DirDelta) {}

	virtual void ApplyMovement(float _DeltaTime) {}

	virtual void CalHorizonVelocityVector(float _DeltaTime) {}

	virtual void CalJumpVelocityVector(float _DeltaTime) {}

	void CalGravityVelocityVector(float _DeltaTime)
	{
		GravityVelocityVector += GravityAccVector * _DeltaTime;

		Color8Bit Color = UContentsFunction::GetCollisionMapImg()->GetColor(GetActorLocation().iX(), GetActorLocation().iY(), UInGameValue::CollisionColor);

		if (UInGameValue::CollisionColor == Color)
		{
			GravityVelocityVector = FVector::Zero;
		}
	}

	void CalTotalVelocityVector(float _DeltaTime)
	{
		TotalVelocityVector = FVector::Zero;
		TotalVelocityVector = TotalVelocityVector + HorizonVelocityVector + GravityVelocityVector + JumpVelocityVector;
	}

	/*void SetMainPlayer(APlayerMario* _MainPlayer)
	{
		MainPlayer = _MainPlayer;
	}*/

	void SetActorState(const EActorState _State)
	{
		ActorState = _State;
	}



	EActorState ActorState = EActorState::None;
	EActorDir ActorDir = EActorDir::Right;
	ECollisionState ActorCollisionState = ECollisionState::None;

	FVector HorizonVelocityVector = FVector::Zero;
	//FVector HorizonAccVector = FVector::Right * 1000.0f;
	//float HorizonMaxSpeed = 500.0f;

	FVector GravityVelocityVector = FVector::Zero;
	FVector GravityAccVector = FVector::Down * 2000.0f;
	FVector TotalVelocityVector = FVector::Zero;
	FVector JumpVelocityVector = FVector::Zero;
	//FVector MaxJumpVelocityVector = FVector::Up * 900.0f;
	//FVector CollisionJumpVelocityVector = FVector::Up * 500.0f;

	//float PFreeMoveVelocity = 1000.0f;
	//static APlayerMario* MainPlayer;
	int Life;

	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;
	std::string CurAnimationName = "None";


private:
};

