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

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	/// <summary>
	/// ������ Ȯ���� �Ŀ� �ش� ������ �������� Idle �ִϸ��̼��̸��� �ٲٰ� ChangeAnimation�� ���ڷ� �ִ´�.
	/// </summary>
	void IdleStart();

	/// <summary>
	/// ������ Ȯ���� �Ŀ� �ش� ������ �������� Move �ִϸ��̼��̸��� �ٲٰ� ChangeAnimation�� ���ڷ� �ִ´�.
	/// </summary>
	void MoveStart();
	
	/// <summary>
	/// FreeMove
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
	/// </summary>
	void GravityCheck(float _DeltaTime);

	/// <summary>
	/// ���� ������ ����� �ִϸ��̼� �̸����� �����ϴ� �Լ�
	/// </summary>
	std::string ChangeAnimationName(std::string _MainName);

	/// <summary>
	/// Actor�� ���� ��ǥ X, Y���� ���� ������ �������� OffSet���� ������ ��ġ�� ��ȯ�ϴ� �Լ�
	/// </summary>
	FVector GetActorOffSetPos();

	/// <summary>
	/// ������ �̵���� (��� �浹�� �����ϰ� ������ �̵� ����)
	/// </summary>
	void FreeMove(float _DeltaTime);
	
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


	EPlayerState MarioState = EPlayerState::None;
	EPlayerDir MarioDir = EPlayerDir::Right;
	float PVelocity = 500.0f;
	float PGravity = 500.0f;
	float PFreeMoveVelocity = 1000.0f;
	UImageRenderer* MarioRenderer = nullptr;
	std::string CurAnimationName = "None";

};

