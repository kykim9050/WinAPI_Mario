#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class UContentsFunction;

class UCollisionMap : public AActor
{
	friend UContentsFunction;
public:
	// constrcuter destructer
	UCollisionMap();
	~UCollisionMap();

	// delete Function
	UCollisionMap(const UCollisionMap& _Other) = delete;
	UCollisionMap(UCollisionMap&& _Other) noexcept = delete;
	UCollisionMap& operator=(const UCollisionMap& _Other) = delete;
	UCollisionMap& operator=(UCollisionMap&& _Other) noexcept = delete;
	
	static UImageRenderer* GetColMapRenderer()
	{
		return CollisionMapRenderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	

private:
	static UImageRenderer* CollisionMapRenderer;
	static UWindowImage* GetCollisionMapImg()
	{
		return CollisionMapRenderer->GetImage();
	}
};

