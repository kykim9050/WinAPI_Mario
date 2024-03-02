#pragma once
#include "ItemUnit.h"


// Ό³Έν :
class AFireFlower : public AItemUnit
{
public:
	// constrcuter destructer
	AFireFlower();
	~AFireFlower();

	// delete Function
	AFireFlower(const AFireFlower& _Other) = delete;
	AFireFlower(AFireFlower&& _Other) noexcept = delete;
	AFireFlower& operator=(const AFireFlower& _Other) = delete;
	AFireFlower& operator=(AFireFlower&& _Other) noexcept = delete;

protected:
	void CollisionCheck() override;

	void FirstInit(float _DeltaTime) override;
	void Appear(float _DeltaTime) override;

	void IdleStart() override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

