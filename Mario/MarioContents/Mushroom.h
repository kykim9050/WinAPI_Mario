#pragma once
#include "ItemUnit.h"

// Ό³Έν :
class AMushroom : public AItemUnit
{
public:
	// constrcuter destructer
	AMushroom();
	~AMushroom();

	// delete Function
	AMushroom(const AMushroom& _Other) = delete;
	AMushroom(AMushroom&& _Other) noexcept = delete;
	AMushroom& operator=(const AMushroom& _Other) = delete;
	AMushroom& operator=(AMushroom&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void MoveStart() override;
	void AppearStart() override;
	void FirstInit(float _DeltaTime) override;
	void Appear(float _DeltaTime) override;
	void Move(float _DeltaTime) override;
	void CollisionCheck() override;
	void GetHitStart() override;
	void CalGravityVelocityVector(float _DeltaTime) override;
	void CalHorizonVelocityVector(float _DeltaTime) override;
	void ResultMovementUpdate(float _DeltaTime) override;

private:
	float GravityVel = 1000.0f;
	float MushroomSpeed = 200.0f;
};

