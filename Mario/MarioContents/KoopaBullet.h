#pragma once
#include "BulletUnit.h"

// Ό³Έν :
class AKoopaBullet : public ABulletUnit
{
public:
	// constrcuter destructer
	AKoopaBullet();
	~AKoopaBullet();

	// delete Function
	AKoopaBullet(const AKoopaBullet& _Other) = delete;
	AKoopaBullet(AKoopaBullet&& _Other) noexcept = delete;
	AKoopaBullet& operator=(const AKoopaBullet& _Other) = delete;
	AKoopaBullet& operator=(AKoopaBullet&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

