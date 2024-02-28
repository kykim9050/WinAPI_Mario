#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


// 설명 :
class APlayerMario : public UStateUnit
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
	/// 방향을 확인한 후에 해당 방향을 기준으로 Idle 애니메이션이름을 바꾸고 ChangeAnimation의 인자로 넣는다.
	/// </summary>
	void IdleStart() override;

	/// <summary>
	/// 방향을 확인한 후에 해당 방향을 기준으로 Move 애니메이션이름을 바꾸고 ChangeAnimation의 인자로 넣는다.
	/// </summary>
	void MoveStart() override;

	/// <summary>
	/// Jump 관련 키를 눌렀을 때, 일정 높이로 뛰어오를 때 취해야 하는 행동에 대한 함수를 포함하고 있다.
	/// </summary>
	void JumpStart() override;


	void CollisionJumpStart();

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
	void StateChange(EActorState _PlayerState) override;

	/// <summary>
	/// Actor의 방향(좌,우)을 확인하고 맴버 변수값으로 지정하는 함수
	/// 기존 방향과 같으면 true, 기존 방향과 다르면 false
	/// </summary>
	bool DirCheck();

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
	void StateUpdate(float _DeltaTime) override;

	/// <summary>
	/// Actor가 Idle 상태에서 취할 수 있는 기능
	/// 1. 중력 적용
	/// 2. 다른 State로의 전환
	/// </summary>
	void Idle(float _DeltaTime) override;

	/// <summary>
	/// Actor가 Move 상태에서 취할 수 있는 기능
	/// 1. 중력 적용
	/// 2. 다른 State로의 전환
	/// 3. 좌우 이동
	/// 4. 장애물에 위치 확인 후 이동 제한
	/// </summary>
	void Move(float _DeltaTime) override;

	void Jump(float _DeltaTime) override;

	void CollisionJump(float _DeltaTime);

	void ReverseMove(float _DeltaTime);

	void CameraPosUpdate(FVector _Player, FVector _MovePos);

	bool IsReverseMove();

	static APlayerMario* GetMainPlayer()
	{
		return MainPlayer;
	}

	void CollisionUpdate(float _DeltaTime) override;

	void CollisionStateChange(ECollisionState _CollisionState) override;

	void GetHit(float _DeltaTime) override;

	void GetHitStart() override;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void BlockBotHitStart();
	void BlockBotHit(float _DeltaTime);


private:
	// 수평 방향 속도 크기에 영향을 끼치는 가속도 관련 벡터
	FVector HorizonAccVector = FVector::Right * 700.0f;
	// 수평 방향 최고 제한 속도의 크기
	float HorizonMaxSpeed = 350.0f;

	FVector InitJumpVelocityVector = FVector::Up * 600.0f;
	FVector CollisionJumpVelocityVector = FVector::Up * 500.0f;

	// FreeMove 작동 시 속도
	float PFreeMoveVelocity = 1000.0f;

	static APlayerMario* MainPlayer;
	void SetMainPlayer(APlayerMario* _MainPlayer)
	{
		MainPlayer = _MainPlayer;
	}

	void AddHorizonVelocityVector(const FVector& _DirDelta) override;
	void ResultMovementUpdate(float _DeltaTime) override;
	void ApplyMovement(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime) override;
	void CalJumpVelocityVector(float _DeltaTime) override;
	void GroundUp();
};

