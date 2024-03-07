#pragma once
#include "MonsterUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"


// Ό³Έν :
class AGoomba : public AMonsterUnit
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

	

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void GetHitStart() override;
	void GetHitFromPlayerStart() override;

	void Idle(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void GetMonsterHit(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime) override;
	//void ResultMovementUpdate(float _DeltaTime) override;

	void CollisionCheck() override;
	void GetMonsterHitStart() override;
	void GetHitFromMonsterStart() override;


private:
	
};

