#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


class AMarioBullet;
// 설명 :
class APlayerMario : public UStateUnit
{
	friend class AUI;

public:
	// constrcuter destructer
	APlayerMario();
	~APlayerMario();

	// delete Function
	APlayerMario(const APlayerMario& _Other) = delete;
	APlayerMario(APlayerMario&& _Other) noexcept = delete;
	APlayerMario& operator=(const APlayerMario& _Other) = delete;
	APlayerMario& operator=(APlayerMario&& _Other) noexcept = delete;

	/// <summary>
	/// Actor의 상태가 변경될 때 실행되는 함수
	/// 각 상태가 시작되기 전에 실행되어야 할 함수를 호출해준다.
	/// </summary>
	/// <param name="_PlayerState"></param>
	void StateChange(EActorState _PlayerState) override;

	void HitBlockBottom()
	{
		BlockBottomHit = true;
	}

	void GetCoin()
	{
		CoinCount += 1;
		UPlayerInfoManager::GetInst().AddAmountOfCoins(1);
	}

	EMarioType GetPlayerType() const
	{
		return MarioType;
	}

	void ReachToCastleGate()
	{
		IsReachingCastleGate = true;
	}

	static APlayerMario* GetMainPlayer()
	{
		return MainPlayer;
	}

	void EattingFireFlower()
	{
		AteFireFlower = true;
	}

	void ReachToStageEnd()
	{
		IsReachingStageEnd = true;
	}

	void EattingMushroom()
	{
		AteMushroom = true;
	}

	void MeetThePrincess()
	{
		MeetPrincess = true;
	}

	static void ReachToBossRoom()
	{
		InTheBossRoom = true;
	}

	EMarioType GetMarioType() const
	{
		return MarioType;
	}

	void SetLeftSideBlockHit()
	{
		LeftSideBlockHit = true;
	}

	void SetRightSideBlockHit()
	{
		RightSideBlockHit = true;
	}

protected:
	

private:
	static bool GetIsReachingCastleGate()
	{
		return IsReachingCastleGate;
	}

	static bool GetIsReachingStageEnd()
	{
		return IsReachingStageEnd;
	}

	void CollisionUpdate(float _DeltaTime) override;
	void CollisionStateCheck();
	void CollisionStateChange(ECollisionState _CollisionState) override;
	void GetHit(float _DeltaTime) override;
	void GetHitStart() override;

	bool IsMeetThePrincess() const
	{
		return MeetPrincess;
	}

	int GetCoinCount() const
	{
		return CoinCount;
	}

	void ReverseMoveCheck();

	/// <summary>
	/// 방향 정보가 적용된 애니메이션 이름으로 수정하는 함수
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName, bool _DirExcept = false, bool _TypeExcept = false);

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

	void DeadStart();

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
	void Changing(float _DeltaTime);
	void Dead(float _DeltaTime);
	void CameraPosUpdate(FVector _MovePos, bool _ExceptCheckRange = false);
	bool IsReverseMove();

	EActorState GetPrevActorState() const
	{
		return PrevActorState;
	}

	void SetPrevActorState(EActorState _State)
	{
		PrevActorState = _State;
	}

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CalGravityVelocityVector(float _DeltaTime) override;
	void DeadCollisionCheck() override;

	void BlockBotHitStart();
	void InvincibleStart();
	void Invincible(float _DeltaTime);
	void BlockSideHitStart();
	void CollisionAction(float _DeltaTime);
	void ChangingFireMarioStart();
	void MarioGrowUpStart();
	void ReachingEndFlagStart();
	void ReachingEndFlag(float _DeltaTime);
	void BossStageClear(float _DeltaTime);
	void ReachStageEnd(float _DeltaTime);
	void ReachStageEndStart();
	void BossStageClearStart();
	void IdleFireThrowStart();
	void MoveFireThrowStart();
	void ReverseMoveFireThrowStart();
	void FallDownStart();
	void JumpFireThrowStart();
	void CeilingCheck();
	void FallDown(float _DeltaTime);
	void IdleFireThrow(float _DeltaTime);
	void MoveFireThrow(float _DeltaTime);
	void ReverseMoveFireThrow(float _DeltaTime);
	void JumpFireThrow(float _DeltaTime);

	void SetPlayerFallDown()
	{
		PlayerFallDown = true;
	}
	bool IsPlayerFallDown() const
	{
		return PlayerFallDown;
	}
	void SetClearBossStage()
	{
		ClearBossStage = true;
	}
	bool GetClearBossStage() const
	{
		return ClearBossStage;
	}
	bool IsReachToBossRoom() const
	{
		return InTheBossRoom;
	}
	void CameraMoveOff()
	{
		CameraMovePause = true;
	}
	void CameraMoveOn()
	{
		CameraMovePause = false;
	}
	bool IsCameraMovePause() const
	{
		return CameraMovePause;
	}
	void SetMainPlayer(APlayerMario* _MainPlayer)
	{
		MainPlayer = _MainPlayer;
	}
	bool GetLeftSideBlockHit() const
	{
		return LeftSideBlockHit;
	}
	bool GetRightSideBlockHit() const
	{
		return RightSideBlockHit;
	}
	

	void AddHorizonVelocityVector(const FVector& _DirDelta) override;
	void ResultMovementUpdate(float _DeltaTime) override;
	void ApplyMovement(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime) override;
	void CalJumpVelocityVector(float _DeltaTime) override;
	void GroundUp();
	void BulletFire();
	void BulletListReleaseUpdate();
	void BulletReloadUpdate(float _DeltaTime);

	UCollision* FootCollision = nullptr;
	AMarioBullet* NewFireBall = nullptr;
	std::list<AMarioBullet*> Bullets = std::list<AMarioBullet*>();

	EMarioType MarioType = EMarioType::None;
	EActorState PrevActorState = EActorState::None;
	FVector HorizonAccVector = FVector::Right * 700.0f;
	FVector InitJumpVelocityVector = FVector::Up * 500.0f;
	FVector CollisionJumpVelocityVector = FVector::Up * 400.0f;
	float HorizonMaxSpeed = 350.0f;
	float PFreeMoveVelocity = 3000.0f;

	static bool IsReachingStageEnd;
	static bool IsReachingCastleGate;
	static APlayerMario* MainPlayer;
	static bool InTheBossRoom;

	bool IsOnTheBlock = false;
	bool AteMushroom = false;
	bool AteFireFlower = false;
	bool IsInvincible = false;
	bool BlockBottomHit = false;
	bool MeetPrincess = false;
	bool ClearBossStage = false;
	bool CameraMovePause = false;
	bool PlayerFallDown = false;
	bool CanUseBullet = true;
	bool LeftSideBlockHit = false;
	bool RightSideBlockHit = false;

	int ThrowBulletNum = 0;
	int CoinCount = 0;
	int DeadStep = 0;
	int ReachingEndStep = 0;
	int BossStageClearStep = 0;
	float DeadDelayTime = 0.5f;
	float BulletReloadTime = 0.3f;
	

};

