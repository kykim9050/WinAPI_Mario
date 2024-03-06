#pragma once
#include <EngineCore/Actor.h>
#include "EnumClass.h"

// Ό³Έν :
class ABackGroundMap : public AActor
{
public:
	// constrcuter destructer
	ABackGroundMap();
	~ABackGroundMap();

	// delete Function
	ABackGroundMap(const ABackGroundMap& _Other) = delete;
	ABackGroundMap(ABackGroundMap&& _Other) noexcept = delete;
	ABackGroundMap& operator=(const ABackGroundMap& _Other) = delete;
	ABackGroundMap& operator=(ABackGroundMap&& _Other) noexcept = delete;

	UImageRenderer* GetMapRenderer() const
	{
		return BackGroundMapRenderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	UImageRenderer* BackGroundMapRenderer = nullptr;
};

