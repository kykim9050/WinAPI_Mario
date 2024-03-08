#pragma once
#include "MonsterUnit.h"

// Ό³Έν :
class AKoopa : public AMonsterUnit
{
public:
	// constrcuter destructer
	AKoopa();
	~AKoopa();

	// delete Function
	AKoopa(const AKoopa& _Other) = delete;
	AKoopa(AKoopa&& _Other) noexcept = delete;
	AKoopa& operator=(const AKoopa& _Other) = delete;
	AKoopa& operator=(AKoopa&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveStart() override;
	void JumpStart() override;
	void FirstInit(float _Deltatime) override;
	void Move(float _DeltaTime) override;
	void Jump(float _DeltaTime) override;

	EActorDir DirCheckAndSet();
	void ChangeAnimationInPlayerDir();
	
	void CheckScopeOfActivity();

	void CollisionCheck() override;

private:
	FVector InitPos = FVector::Zero;
	float MoveTime = 1.0f;
	float KoopaSpeed = 50.0f;
	float KoopaJump = 400.0f;
};

