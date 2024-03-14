#pragma once
#include <EngineCore/Actor.h>
#include "UIBaseInfo.h"

// Ό³Έν :
class ALevelIntro : public AUIBaseInfo
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

	void NumberToAnimation(int _PrintNumber, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer);

private:
	UImageRenderer* UIRenderer = nullptr;
	
	int IntroLife = 0;
	std::vector<UImageRenderer*> LifeRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> StageInfoCenterRenderer = std::vector<UImageRenderer*>();

	float RenderingTime = 2.0f;
	bool IsPlaying = true;
};

