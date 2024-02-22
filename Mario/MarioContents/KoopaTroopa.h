#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"

// Ό³Έν :
class AKoopaTroopa : public AActor
{
public:
	// constrcuter destructer
	AKoopaTroopa();
	~AKoopaTroopa();

	// delete Function
	AKoopaTroopa(const AKoopaTroopa& _Other) = delete;
	AKoopaTroopa(AKoopaTroopa&& _Other) noexcept = delete;
	AKoopaTroopa& operator=(const AKoopaTroopa& _Other) = delete;
	AKoopaTroopa& operator=(AKoopaTroopa&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime);

	void Move(float _DeltaTime);

	void ResultMovementUpdate(float _DeltaTime);


protected:

private:
	UImageRenderer* Renderer = nullptr;
	UCollision* BodyCollision = nullptr;

	EActorState ActorState = EActorState::None;
	ECollisionState ActorCollisionState = ECollisionState::None;

	FVector HorizonVelocityVector = FVector::Zero;
	FVector GravityVelocityVector = FVector::Zero;
	FVector TotalVelocityVector = FVector::Zero;

	int Life = 2;
	bool KillPlayer = false;

	void SetActorState(const EActorState _State)
	{
		ActorState = _State;
	}
};

