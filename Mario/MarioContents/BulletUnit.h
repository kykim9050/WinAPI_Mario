#pragma once
#include "StateUnit.h"

// Ό³Έν :
class ABulletUnit : public UStateUnit
{
public:
	// constrcuter destructer
	ABulletUnit();
	~ABulletUnit();

	// delete Function
	ABulletUnit(const ABulletUnit& _Other) = delete;
	ABulletUnit(ABulletUnit&& _Other) noexcept = delete;
	ABulletUnit& operator=(const ABulletUnit& _Other) = delete;
	ABulletUnit& operator=(ABulletUnit&& _Other) noexcept = delete;

protected:
	
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void StateUpdate(float _DeltaTime) override;
	void StateChange(EActorState _ActorState) override;

	virtual void MoveStart() {};
	virtual void FirstInit(float _DeltaTime) {};
	virtual void Move(float _DeltaTime) {};

	void ThrowBullet()
	{
		BulletMoveStart = true;
	}

	bool IsBulletFire() const
	{
		return BulletMoveStart;
	}

private:
	
	bool BulletMoveStart = false;
};

