#pragma once
#include <EngineCore/Actor.h>
#include "InGameValue.h"
#include "EnumClass.h"


// ���� :
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

	int IntroScore = 0;
	int IntroAmountOfCoins = 0;
	std::vector<UImageRenderer*> ScoreRenderer = std::vector<UImageRenderer*>();
	std::vector<UImageRenderer*> CoinCountRenderer = std::vector<UImageRenderer*>();



private:

};

