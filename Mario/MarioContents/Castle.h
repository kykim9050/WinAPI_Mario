#pragma once
#include "StructureUnit.h"

// Ό³Έν :
class ACastle : public AStructureUnit
{
public:
	// constrcuter destructer
	ACastle();
	~ACastle();

	// delete Function
	ACastle(const ACastle& _Other) = delete;
	ACastle(ACastle&& _Other) noexcept = delete;
	ACastle& operator=(const ACastle& _Other) = delete;
	ACastle& operator=(ACastle&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck() override;


private:
	UImageRenderer* FlagRenderer = nullptr;
};

