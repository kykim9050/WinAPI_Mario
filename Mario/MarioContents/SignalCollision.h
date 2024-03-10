#pragma once
#include "StructureUnit.h"

// Ό³Έν :
class USignalCollision : public AStructureUnit
{
public:
	// constrcuter destructer
	USignalCollision();
	~USignalCollision();

	// delete Function
	USignalCollision(const USignalCollision& _Other) = delete;
	USignalCollision(USignalCollision&& _Other) noexcept = delete;
	USignalCollision& operator=(const USignalCollision& _Other) = delete;
	USignalCollision& operator=(USignalCollision&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void CollisionCheck() override;

private:

};

