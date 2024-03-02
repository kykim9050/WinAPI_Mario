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
	//void CollisionCheck() override;
	//void CollisionStateChange(ECollisionState _CollisionState) override;

	void FirstInit(float _DeltaTime) override;
	//void Idle(float _DeltaTime) override;
	//void Move(float _DeltaTime) override;
	void Appear(float _DeltaTime) override;


	//void AppearStart() override;
	//void MoveStart() override;
	//void ReleaseStart() override;
	//void GetHitStart() override;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

