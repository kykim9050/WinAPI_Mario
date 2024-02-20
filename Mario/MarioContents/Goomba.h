#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"


// Ό³Έν :
class AGoomba : public AActor
{
public:
	// constrcuter destructer
	AGoomba();
	~AGoomba();

	// delete Function
	AGoomba(const AGoomba& _Other) = delete;
	AGoomba(AGoomba&& _Other) noexcept = delete;
	AGoomba& operator=(const AGoomba& _Other) = delete;
	AGoomba& operator=(AGoomba&& _Other) noexcept = delete;

	void StateUpdate(float _DeltaTime);

	void SetActorState(const EPlayerState _State)
	{
		ActorState = _State;
	}

	void Move(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* Renderer = nullptr;

	FVector HorizonVelocityVector = FVector::Zero;
	EPlayerState ActorState = EPlayerState::None;

};

