#pragma once
#include "BulletUnit.h"

// Ό³Έν :
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

private:

};

