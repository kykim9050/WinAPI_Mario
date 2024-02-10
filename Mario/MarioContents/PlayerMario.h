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
	void FreeMove(float _DeltaTime);
	void StateUpdate(float _DeltaTime);
	void Idle(float _DeltaTime);

	PlayerState MarioState = PlayerState::None;
	float PVelocity = 500.0f;


};

