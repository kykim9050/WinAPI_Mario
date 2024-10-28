#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"


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

	/// <summary>
	/// FreeMove������ �ִϸ��̼� ����
	/// </summary>
	void FreeMoveStart();

	/// <summary>
	/// Actor�� ���°� ����� �� ����Ǵ� �Լ�
	/// �� ���°� ���۵Ǳ� ���� ����Ǿ�� �� �Լ��� ȣ�����ش�.
	/// </summary>
	/// <param name="_PlayerState"></param>
	void StateChange(EPlayerState _PlayerState);

	/// <summary>
	/// Actor�� ����(��,��)�� Ȯ���ϰ� �ɹ� ���������� �����ϴ� �Լ�
	/// </summary>
	void DirCheck();

	/// <summary>
	/// �ȼ� �浹�� Ȱ���� �߷�üũ �Լ�
	/// bool ���� ��ȯ�ϴµ�, ��ֹ��� �����ϸ� true, �������̸� false�� ��ȯ
	/// </summary>
	bool GravityCheck(float _DeltaTime);

	/// <summary>
	/// ���� ������ ����� �ִϸ��̼� �̸����� �����ϴ� �Լ�
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName);

	/// <summary>
	/// Actor�� ���� ��ǥ X, Y���� ���� ������ �������� OffSet���� ������ ��ġ�� ��ȯ�ϴ� �Լ�
	/// </summary>
	FVector GetActorOffSetPos();

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

	/// <summary>
	/// Actor�� ������ ����
	/// </summary>
	void SetMarioDir(const EPlayerDir _Dir)
	{
		MarioDir = _Dir;
	}

	/// <summary>
	/// Actor�� �� ���¸� ����
	/// </summary>
	void SetMarioState(const EPlayerState _State)
	{
		MarioState = _State;
	}

	void CameraPosUpdate(FVector _Player, FVector _MovePos);


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	// �÷��̾��� ���� ����
	EPlayerState MarioState = EPlayerState::None;
	// �÷��̾��� ���� ���� (��, ��)
	EPlayerDir MarioDir = EPlayerDir::Right;

	// ���� ���� �ӵ��� ���� ����
	FVector HorizonVelocityVector = FVector::Zero;
	// ���� ���� �ӵ� ũ�⿡ ������ ��ġ�� ���ӵ� ���� ����
	FVector HorizonAccVector = FVector::Right * 1000.0f;
	// ���� ���� �ְ� ���� �ӵ��� ũ��
	float HorizonMaxSpeed = 500.0f;

	float PMaxVelocity = 500.0f;
	float PJumpVelocity = 500.0f;
	float PVelocity = 0.0f;
	float PAcceleration = 300.0f;
	float PGravity = 500.0f;
	float PFreeMoveVelocity = 1000.0f;
	float PJumpHeightLimit = 0.0f;
	bool JumpEnd = false;

	UImageRenderer* MarioRenderer = nullptr;
	std::string CurAnimationName = "None";


	void AddHorizonVelocityVector(const FVector& _DirDelta);
	void ResultMovementUpdate(float _DeltaTime);
	void ApplyMovement(float _DeltaTime);
	void CalHorizonVelocityVector(float _DeltaTime);
};

