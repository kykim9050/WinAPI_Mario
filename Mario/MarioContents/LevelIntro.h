#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ALevelIntro : public AActor
{
public:
	// constrcuter destructer
	ALevelIntro();
	~ALevelIntro();

	// delete Function
	ALevelIntro(const ALevelIntro& _Other) = delete;
	ALevelIntro(ALevelIntro&& _Other) noexcept = delete;
	ALevelIntro& operator=(const ALevelIntro& _Other) = delete;
	ALevelIntro& operator=(ALevelIntro&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

