#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "ContentsFunction.h"
#include "InGameValue.h"


// ���� :
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
	// ���� ���� �ӵ� ũ�⿡ ������ ��ġ�� ���ӵ� ���� ����
	FVector HorizonAccVector = FVector::Right * 700.0f;
	// ���� ���� �ְ� ���� �ӵ��� ũ��
	float HorizonMaxSpeed = 350.0f;

	FVector InitJumpVelocityVector = FVector::Up * 600.0f;
	FVector CollisionJumpVelocityVector = FVector::Up * 500.0f;

	// FreeMove �۵� �� �ӵ�
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

