#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


class AMarioBullet;
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

	/// <summary>
	/// Actor�� ���°� ����� �� ����Ǵ� �Լ�
	/// �� ���°� ���۵Ǳ� ���� ����Ǿ�� �� �Լ��� ȣ�����ش�.
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

	int ThrowBulletNum = 0;
	int CoinCount = 0;
	int DeadStep = 0;
	int ReachingEndStep = 0;
	int BossStageClearStep = 0;
	float DeadDelayTime = 0.5f;
	float BulletReloadTime = 0.3f;
	

};

