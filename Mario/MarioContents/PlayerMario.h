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
	void FreeMoveStart(float _DeltaTime);
	void CameraMoveStart(float _DeltaTime);
	void IdleStart(float _DeltaTime);
	void MoveStart(float _DeltaTime);
	void JumpStart(float _DeltaTime);

	void FreeMove(float _DeltaTime);
	void StateUpdate(float _DeltaTime);
	void Idle(float _DeltaTime);
	void Move(float _DeltaTime);

	void SetMarioDir(const EPlayerDir _Dir)
	{
		MarioDir = _Dir;
	}

	EPlayerState MarioState = EPlayerState::None;
	EPlayerDir MarioDir = EPlayerDir::Right;
	float PVelocity = 500.0f;
	UImageRenderer* MarioRenderer = nullptr;

};

