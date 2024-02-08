#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AEndingBackGround : public AActor
{
public:
	// constrcuter destructer
	AEndingBackGround();
	~AEndingBackGround();

	// delete Function
	AEndingBackGround(const AEndingBackGround& _Other) = delete;
	AEndingBackGround(AEndingBackGround&& _Other) noexcept = delete;
	AEndingBackGround& operator=(const AEndingBackGround& _Other) = delete;
	AEndingBackGround& operator=(AEndingBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

