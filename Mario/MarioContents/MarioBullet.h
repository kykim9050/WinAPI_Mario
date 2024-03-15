#pragma once
#include "BulletUnit.h"

class APlayerMario;
// Ό³Έν :
class AMarioBullet : public ABulletUnit
{
	friend APlayerMario;
public:
	// constrcuter destructer
	AMarioBullet();
	~AMarioBullet();

	// delete Function
	AMarioBullet(const AMarioBullet& _Other) = delete;
	AMarioBullet(AMarioBullet&& _Other) noexcept = delete;
	AMarioBullet& operator=(const AMarioBullet& _Other) = delete;
	AMarioBullet& operator=(AMarioBullet&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void FallDownStart() override;
	void ExplosionStart() override;
	void ReleaseStart() override;
	void Move(float _DeltaTime) override;
	void FallDown(float _DeltaTime) override;
	void Explosion(float _DeltaTime) override;
	void CalJumpVelocityVector(float _DeltaTime) override;
	void CalGravityVelocityVector(float _DeltaTime) override;

	bool WallCollisionCheck();
	bool FallDownGroundCheck();	
	void SetDir(EActorDir _OtherDir);
	FVector GetMoveDir();

private:
	float FallDownGravityVel = 500.0f;
	float GravityAccVel = 2000.0f;
	float JumpPowerVel = 400.0f;
	float SpeedVel = 700.0f;
};

