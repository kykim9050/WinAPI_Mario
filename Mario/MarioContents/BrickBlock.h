#pragma once
#include "BlockUnit.h"


class ADebrisBlock : public AActor
{
	friend class ABrickBlock;

public:
	UImageRenderer* Renderer = nullptr;
};

// Ό³Έν :
class ABrickBlock : public ABlockUnit
{
public:
	// constrcuter destructer
	ABrickBlock();
	~ABrickBlock();

	// delete Function
	ABrickBlock(const ABrickBlock& _Other) = delete;
	ABrickBlock(ABrickBlock&& _Other) noexcept = delete;
	ABrickBlock& operator=(const ABrickBlock& _Other) = delete;
	ABrickBlock& operator=(ABrickBlock&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void IdleStart() override;
	void MoveStart() override;

	void FirstInit(float _Deltatime) override;
	void Move(float _DeltaTime) override;
	void Debris(float _DeltaTime) override;

	void CollisionCheck() override;

	void DebrisStart() override;

private:

	UImageRenderer* DebrisingRenderer = nullptr;

	float Debrisingtime = 0.375f;
};

