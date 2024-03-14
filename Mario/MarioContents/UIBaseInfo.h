#pragma once
#include <EngineCore/Actor.h>



// Ό³Έν :
class AUIBaseInfo : public AActor
{
public:
	// constrcuter destructer
	AUIBaseInfo();
	~AUIBaseInfo();

	// delete Function
	AUIBaseInfo(const AUIBaseInfo& _Other) = delete;
	AUIBaseInfo(AUIBaseInfo&& _Other) noexcept = delete;
	AUIBaseInfo& operator=(const AUIBaseInfo& _Other) = delete;
	AUIBaseInfo& operator=(AUIBaseInfo&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void NumberToAnimation(int _PrintNumber, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer);

	int IntroScore = 0;
	int IntroAmountOfCoins = 0;
	std::vector<std::string> IntroStageInfo = std::vector<std::string>();
	std::vector<UImageRenderer*> ScoreRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> CoinCountRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> StageInfoRenderer = std::vector<UImageRenderer*>();

private:

};

