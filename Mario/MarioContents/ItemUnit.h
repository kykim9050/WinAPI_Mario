#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"
#include "InGameValue.h"

class UImageRenderer;

// Ό³Έν :
class AItemUnit : public AActor
{
	friend class ABlockUnit;
public:
	// constrcuter destructer
	AItemUnit();
	~AItemUnit();

	// delete Function
	AItemUnit(const AItemUnit& _Other) = delete;
	AItemUnit(AItemUnit&& _Other) noexcept = delete;
	AItemUnit& operator=(const AItemUnit& _Other) = delete;
	AItemUnit& operator=(AItemUnit&& _Other) noexcept = delete;

	void StateUpdate(float _DeltaTime);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	EActorState ActorState = EActorState::None;
	UImageRenderer* Renderer = nullptr;

};

