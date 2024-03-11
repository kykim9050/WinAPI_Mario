#pragma once
#include "MonsterUnit.h"


class AKoopaBullet;
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

	static const bool GetKoopaIsDead()
	{
		return KoopaIsDead;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void MoveStart() override;
	void JumpStart() override;
	void FireStart() override;
	void FallDownStart() override;

	void FirstInit(float _Deltatime) override;
	void Move(float _DeltaTime) override;
	void Jump(float _DeltaTime) override;
	void Fire(float _DeltaTime) override;
	void FallDown(float _DeltaTime) override;

	EActorDir DirCheckAndSet();
	void ChangeAnimationInPlayerDir();
	
	void CheckScopeOfActivity();

	void CollisionCheck() override;

	void DeadCollisionCheck() override;

private:
	std::list<AKoopaBullet*> Bullets = std::list<AKoopaBullet*>();
	AKoopaBullet* NewBullet = nullptr;

	FVector InitPos = FVector::Zero;
	float MoveTime = 1.0f;
	float FireDelayTime = 2.5f;
	float FiringTime = 0.5f;

	float KoopaSpeed = 50.0f;
	float KoopaJump = 400.0f;

	void BulletListReleaseUpdate();
	bool Dying = false;
	bool FallingDown = false;

	static bool KoopaIsDead;
	void SetKoopaIsDead()
	{
		KoopaIsDead = true;
	}
};

