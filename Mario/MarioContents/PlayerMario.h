#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


// ���� :
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

	void ReverseMoveCheck();

	/// <summary>
	/// ���� ������ ����� �ִϸ��̼� �̸����� �����ϴ� �Լ�
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName, bool _DirExcept = false, bool _TypeExcept = false);

	/// <summary>
	/// ������ Ȯ���� �Ŀ� �ش� ������ �������� Idle �ִϸ��̼��̸��� �ٲٰ� ChangeAnimation�� ���ڷ� �ִ´�.
	/// </summary>
	void IdleStart() override;

	/// <summary>
	/// ������ Ȯ���� �Ŀ� �ش� ������ �������� Move �ִϸ��̼��̸��� �ٲٰ� ChangeAnimation�� ���ڷ� �ִ´�.
	/// </summary>
	void MoveStart() override;

	/// <summary>
	/// Jump ���� Ű�� ������ ��, ���� ���̷� �پ���� �� ���ؾ� �ϴ� �ൿ�� ���� �Լ��� �����ϰ� �ִ�.
	/// </summary>
	void JumpStart() override;

	void DeadStart();

	void CollisionJumpStart();

	/// <summary>
	/// FreeMove������ �ִϸ��̼� ����
	/// </summary>
	void FreeMoveStart();

	/// <summary>
	/// ReverseMove�ÿ� �ִϸ��̼� ����
	/// </summary>
	void ReverseMoveStart();


	/// <summary>
	/// Actor�� ���°� ����� �� ����Ǵ� �Լ�
	/// �� ���°� ���۵Ǳ� ���� ����Ǿ�� �� �Լ��� ȣ�����ش�.
	/// </summary>
	/// <param name="_PlayerState"></param>
	void StateChange(EActorState _PlayerState) override;

	/// <summary>
	/// Actor�� ����(��,��)�� Ȯ���ϰ� �ɹ� ���������� �����ϴ� �Լ�
	/// ���� ����� ������ true, ���� ����� �ٸ��� false
	/// </summary>
	bool DirCheck();

	/// <summary>
	/// ī�޶�. �÷��̾� �̵���� (������. ��� �浹�� �����ϰ� ������ �̵� ����)
	/// </summary>
	void FreeMove(float _DeltaTime);

	/// <summary>
	/// ī�޶� �̵��� �� �ִ� ��� (������)
	/// </summary>
	/// <param name="_DeltaTime"></param>
	void CameraMove(float _DeltaTime);

	/// <summary>
	/// ���¸� üũ�ϸ� �� ���¿� �´� �Լ��� ȣ��
	/// </summary>
	void StateUpdate(float _DeltaTime) override;

	/// <summary>
	/// Actor�� Idle ���¿��� ���� �� �ִ� ���
	/// 1. �߷� ����
	/// 2. �ٸ� State���� ��ȯ
	/// </summary>
	void Idle(float _DeltaTime) override;

	/// <summary>
	/// Actor�� Move ���¿��� ���� �� �ִ� ���
	/// 1. �߷� ����
	/// 2. �ٸ� State���� ��ȯ
	/// 3. �¿� �̵�
	/// 4. ��ֹ��� ��ġ Ȯ�� �� �̵� ����
	/// </summary>
	void Move(float _DeltaTime) override;
	void Jump(float _DeltaTime) override;
	void CollisionJump(float _DeltaTime);
	void ReverseMove(float _DeltaTime);
	void Changing(float _DeltaTime);
	void Dead(float _DeltaTime);
	void CameraPosUpdate(FVector _MovePos, bool _ExceptCheckRange = false);
	bool IsReverseMove();

	static APlayerMario* GetMainPlayer()
	{
		return MainPlayer;
	}

	static bool GetIsReachingCastleGate()
	{
		return IsReachingCastleGate;
	}

	static bool GetIsReachingStageEnd()
	{
		return IsReachingStageEnd;
	}

	static void ReachToBossRoom()
	{
		InTheBossRoom = true;
	}

	void CollisionUpdate(float _DeltaTime) override;
	void CollisionStateCheck();
	void CollisionStateChange(ECollisionState _CollisionState) override;
	void GetHit(float _DeltaTime) override;
	void GetHitStart() override;
	
	void EattingMushroom()
	{
		AteMushroom = true;
	}

	void EattingFireFlower()
	{
		AteFireFlower = true;
	}

	void HitBlockBottom()
	{
		BlockBottomHit = true;
	}

	void ReachToStageEnd()
	{
		IsReachingStageEnd = true;
	}

	void ReachToCastleGate()
	{
		IsReachingCastleGate = true;
	}

	void MeetThePrincess()
	{
		MeetPrincess = true;
	}

	bool IsMeetThePrincess() const
	{
		return MeetPrincess;
	}

	EMarioType GetPlayerType() const
	{
		return MarioType;
	}

	void GetCoin()
	{
		CoinCount += 1;
		UPlayerInfoManager::GetInst().AddAmountOfCoins(1);
	}

	int GetCoinCount()
	{
		return CoinCount;
	}


protected:
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
	void CeilingCheck();

private:
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

	void AddHorizonVelocityVector(const FVector& _DirDelta) override;
	void ResultMovementUpdate(float _DeltaTime) override;
	void ApplyMovement(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime) override;
	void CalJumpVelocityVector(float _DeltaTime) override;
	void GroundUp();

	UCollision* FootCollision = nullptr;

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

	int CoinCount = 0;
	int DeadStep = 0;
	int ReachingEndStep = 0;
	int BossStageClearStep = 0;
	float DeadDelayTime = 0.5f;

};

