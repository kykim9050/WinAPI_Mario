#pragma once
#include "BulletUnit.h"

// ���� :
class AMarioBullet : public ABulletUnit
{
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
	void MoveStart() override;
	void Move(float _DeltaTime) override;
	void CalJumpVelocityVector(float _DeltaTime) override;
	void CalGravityVelocityVector(float _DeltaTime) override;

private:
	float GravityAccVel = 2000.0f;
	float JumpPowerVel = 500.0f;
};

