#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


// 설명 :
class APlayerMario : public AActor
{
public:
	// constrcuter destructer
	APlayerMario();
	~APlayerMario();

	// delete Function
	APlayerMario(const APlayerMario& _Other) = delete;
	APlayerMario(APlayerMario&& _Other) noexcept = delete;
	APlayerMario& operator=(const APlayerMario& _Other) = delete;
	APlayerMario& operator=(APlayerMario&& _Other) noexcept = delete;

	void ReverseMoveCheck();

	/// <summary>
	/// 가속 계산을 위한 함수
	/// </summary>
	void Accel(float _DeltaTime);

	/// <summary>
	/// 방향을 확인한 후에 해당 방향을 기준으로 Idle 애니메이션이름을 바꾸고 ChangeAnimation의 인자로 넣는다.
	/// </summary>
	void IdleStart();

	/// <summary>
	/// 방향을 확인한 후에 해당 방향을 기준으로 Move 애니메이션이름을 바꾸고 ChangeAnimation의 인자로 넣는다.
	/// </summary>
	void MoveStart();

	/// <summary>
	/// Jump 관련 키를 눌렀을 때, 일정 높이로 뛰어오를 때 취해야 하는 행동에 대한 함수를 포함하고 있다.
	/// </summary>
	void JumpStart();

	/// <summary>
	/// FreeMove용으로 애니메이션 변경
	/// </summary>
	void FreeMoveStart();

	/// <summary>
	/// ReverseMove시에 애니메이션 변경
	/// </summary>
	void ReverseMoveStart();

	/// <summary>
	/// Actor의 상태가 변경될 때 실행되는 함수
	/// 각 상태가 시작되기 전에 실행되어야 할 함수를 호출해준다.
	/// </summary>
	/// <param name="_PlayerState"></param>
	void StateChange(EPlayerState _PlayerState);

	/// <summary>
	/// Actor의 방향(좌,우)을 확인하고 맴버 변수값으로 지정하는 함수
	/// 기존 방향과 같으면 true, 기존 방향과 다르면 false
	/// </summary>
	bool DirCheck();

	/// <summary>
	/// 방향 정보가 적용된 애니메이션 이름으로 수정하는 함수
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName);

	/// <summary>
	/// 카메라. 플레이어 이동기능 (디버깅용. 모든 충돌을 무시하고 빠르게 이동 가능)
	/// </summary>
	void FreeMove(float _DeltaTime);

	/// <summary>
	/// 카메라만 이동할 수 있는 기능 (디버깅용)
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void CameraMove(float _DeltaTime);

	/// <summary>
	/// 상태를 체크하며 각 상태에 맞는 함수를 호출
	/// </summary>
	void StateUpdate(float _DeltaTime);

	/// <summary>
	/// Actor가 Idle 상태에서 취할 수 있는 기능
	/// 1. 중력 적용
	/// 2. 다른 State로의 전환
	/// </summary>
	void Idle(float _DeltaTime);

	/// <summary>
	/// Actor가 Move 상태에서 취할 수 있는 기능
	/// 1. 중력 적용
	/// 2. 다른 State로의 전환
	/// 3. 좌우 이동
	/// 4. 장애물에 위치 확인 후 이동 제한
	/// </summary>
	void Move(float _DeltaTime);

	/// <summary>
	/// Actor가 jump 상태에서 취할 수 있는 기능
	/// 1. 중력 적용
	/// 
	/// </summary>
	void Jump(float _DeltaTime);

	void ReverseMove(float _DeltaTime);

	/// <summary>
	/// Actor의 방향을 수정
	/// </summary>
	void SetMarioDir(const EPlayerDir _Dir)
	{
		MarioDir = _Dir;
	}

	/// <summary>
	/// Actor의 현 상태를 수정
	/// </summary>
	void SetMarioState(const EPlayerState _State)
	{
		MarioState = _State;
	}

	void CameraPosUpdate(FVector _Player, FVector _MovePos);

	bool IsReverseMove();

	static APlayerMario* GetMainPlayer()
	{
		return MainPlayer;
	}

	void CollisionUpdate(float _DeltaTime);

	void SetMarioCollisionState(ECollisionState _CollisionState);

	void GetHit(float _DeltaTime);
	void GetHitStart(float _DeltaTime);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// 플레이어의 현재 상태
	EPlayerState MarioState = EPlayerState::None;
	// 플레이어의 현재 방향 (좌, 우)
	EPlayerDir MarioDir = EPlayerDir::Right;
	// 플레이어의 현재 콜리젼 상태
	ECollisionState MarioCollisionState = ECollisionState::None;

	// 수평 방향 속도에 대한 벡터
	FVector HorizonVelocityVector = FVector::Zero;
	// 수평 방향 속도 크기에 영향을 끼치는 가속도 관련 벡터
	FVector HorizonAccVector = FVector::Right * 1000.0f;
	// 수평 방향 최고 제한 속도의 크기
	float HorizonMaxSpeed = 500.0f;


	// 중력 방향 속도에 대한 벡터
	FVector GravityVelocityVector = FVector::Zero;
	// 중력 방향 속도 크기에 영향을 끼치는 중력 가속도 벡터
	FVector GravityAccVector = FVector::Down * 2000.0f;
	// Player에 작용하는 모든 벡터에 대한 총합 벡터
	FVector TotalVelocityVector = FVector::Zero;
	FVector JumpVelocityVector = FVector::Zero;
	FVector MaxJumpVelocityVector = FVector::Up * 900.0f;

	// FreeMove 작동 시 속도
	float PFreeMoveVelocity = 1000.0f;


	static APlayerMario* MainPlayer;
	void SetMainPlayer(APlayerMario* _MainPlayer)
	{
		MainPlayer = _MainPlayer;
	}


	UImageRenderer* MarioRenderer = nullptr;
	UCollision* BodyCollision = nullptr;
	std::string CurAnimationName = "None";


	void AddHorizonVelocityVector(const FVector& _DirDelta);
	void ResultMovementUpdate(float _DeltaTime);
	void ApplyMovement(float _DeltaTime);
	void CalHorizonVelocityVector(float _DeltaTime);
	void CalGravityVelocityVector(float _DeltaTime);
	void CalTotalVelocityVector(float _DeltaTime);
	void CalJumpVelocityVector(float _DeltaTime);
};

