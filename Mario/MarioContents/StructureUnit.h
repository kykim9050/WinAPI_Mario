#pragma once
#include "StateUnit.h"
#include "MainPlayer.h"

// Ό³Έν :
class AStructureUnit : public UStateUnit, public UMainPlayer
{
public:
	// constrcuter destructer
	AStructureUnit();
	~AStructureUnit();

	// delete Function
	AStructureUnit(const AStructureUnit& _Other) = delete;
	AStructureUnit(AStructureUnit&& _Other) noexcept = delete;
	AStructureUnit& operator=(const AStructureUnit& _Other) = delete;
	AStructureUnit& operator=(AStructureUnit&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	virtual void CollisionCheck() {};

	void StateChange(EActorState _ActorState) override;
	void StateUpdate(float _DeltaTime) override;

	virtual void FallDown(float _DeltaTime) {};
	virtual void FallDownStart() {};

private:

};

