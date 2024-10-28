#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


// ���� :
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
	/// ���� ����� ���� �Լ�
	/// </summary>
	void Accel(float _DeltaTime);

	/// <summary>
	/// ������ Ȯ���� �Ŀ� �ش� ������ �������� Idle �ִϸ��̼��̸��� �ٲٰ� ChangeAnimation�� ���ڷ� �ִ´�.
	/// </summary>
	void IdleStart();

	/// <summary>
	/// ������ Ȯ���� �Ŀ� �ش� ������ �������� Move �ִϸ��̼��̸��� �ٲٰ� ChangeAnimation�� ���ڷ� �ִ´�.
	/// </summary>
	void MoveStart();

	/// <summary>
	/// Jump ���� Ű�� ������ ��, ���� ���̷� �پ���� �� ���ؾ� �ϴ� �ൿ�� ���� �Լ��� �����ϰ� �ִ�.
	/// </summary>
	void JumpStart();

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
	void StateChange(EActorState _PlayerState);

	/// <summary>
	/// Actor�� ����(��,��)�� Ȯ���ϰ� �ɹ� ���������� �����ϴ� �Լ�
	/// ���� ����� ������ true, ���� ����� �ٸ��� false
	/// </summary>
	bool DirCheck();

	/// <summary>
	/// ���� ������ ����� �ִϸ��̼� �̸����� �����ϴ� �Լ�
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName);

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
	void StateUpdate(float _DeltaTime);

	/// <summary>
	/// Actor�� Idle ���¿��� ���� �� �ִ� ���
	/// 1. �߷� ����
	/// 2. �ٸ� State���� ��ȯ
	/// </summary>
	void Idle(float _DeltaTime);

	/// <summary>
	/// Actor�� Move ���¿��� ���� �� �ִ� ���
	/// 1. �߷� ����
	/// 2. �ٸ� State���� ��ȯ
	/// 3. �¿� �̵�
	/// 4. ��ֹ��� ��ġ Ȯ�� �� �̵� ����
	/// </summary>
	void Move(float _DeltaTime);

	/// <summary>
	/// Actor�� jump ���¿��� ���� �� �ִ� ���
	/// 1. �߷� ����
	/// 
	/// </summary>
	void Jump(float _DeltaTime);

	void CollisionJump(float _DeltaTime);

	void ReverseMove(float _DeltaTime);

	/// <summary>
	/// Actor�� ������ ����
	/// </summary>
	void SetMarioDir(const EPlayerDir _Dir)
	{
		MarioDir = _Dir;
	}

	

	void CameraPosUpdate(FVector _Player, FVector _MovePos);

	bool IsReverseMove();

	static APlayerMario* GetMainPlayer()
	{
		return MainPlayer;
	}

	void CollisionUpdate(float _DeltaTime);

	void CollisionStateChange(ECollisionState _CollisionState);

	void SetCollisionState(ECollisionState _CollisionState)
	{
		ActorCollisionState = _CollisionState;
	}

	UCollision* GetBodyCollision()
	{
		return BodyCollision;
	}

	void GetHit(float _DeltaTime);

	void GetHitStart();


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// �÷��̾��� ���� ����
	EActorState MarioState = EActorState::None;
	// �÷��̾��� ���� ���� (��, ��)
	EPlayerDir MarioDir = EPlayerDir::Right;
	// �÷��̾��� ���� �ݸ��� ����
	ECollisionState ActorCollisionState = ECollisionState::None;

	// ���� ���� �ӵ��� ���� ����
	FVector HorizonVelocityVector = FVector::Zero;
	// ���� ���� �ӵ� ũ�⿡ ������ ��ġ�� ���ӵ� ���� ����
	FVector HorizonAccVector = FVector::Right * 1000.0f;
	// ���� ���� �ְ� ���� �ӵ��� ũ��
	float HorizonMaxSpeed = 500.0f;


	// �߷� ���� �ӵ��� ���� ����
	FVector GravityVelocityVector = FVector::Zero;
	// �߷� ���� �ӵ� ũ�⿡ ������ ��ġ�� �߷� ���ӵ� ����
	FVector GravityAccVector = FVector::Down * 2000.0f;
	// Player�� �ۿ��ϴ� ��� ���Ϳ� ���� ���� ����
	FVector TotalVelocityVector = FVector::Zero;
	FVector JumpVelocityVector = FVector::Zero;
	FVector MaxJumpVelocityVector = FVector::Up * 900.0f;
	FVector CollisionJumpVelocityVector = FVector::Up * 400.0f;

	// FreeMove �۵� �� �ӵ�
	float PFreeMoveVelocity = 1000.0f;


	static APlayerMario* MainPlayer;
	void SetMainPlayer(APlayerMario* _MainPlayer)
	{
		MainPlayer = _MainPlayer;
	}

	/// <summary>
	/// Actor�� �� ���¸� ����
	/// </summary>
	void SetMarioState(const EActorState _State)
	{
		MarioState = _State;
	}

	// �÷��̾��� ��� ����Ʈ 3��
	static int Life;

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

