#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class BackGroundMap : public AActor
{
public:
	// constrcuter destructer
	BackGroundMap();
	~BackGroundMap();

	// delete Function
	BackGroundMap(const BackGroundMap& _Other) = delete;
	BackGroundMap(BackGroundMap&& _Other) noexcept = delete;
	BackGroundMap& operator=(const BackGroundMap& _Other) = delete;
	BackGroundMap& operator=(BackGroundMap&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

