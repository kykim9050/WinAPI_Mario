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

	void NumberToAnimation(int _PrintNumber, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer);

private:
	UImageRenderer* UIRenderer = nullptr;

	int IntroScore = 0;
	int IntroLife = 0;
	int IntroAmountOfCoins = 0;
	std::vector<std::string> IntroStageInfo = std::vector<std::string>();
	std::vector<UImageRenderer*> ScoreRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> CoinCountRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> StageInfoRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> StageInfoCenterRenderer = std::vector<UImageRenderer*>();

	float RenderingTime = 2.0f;
	bool IsPlaying = true;

};

