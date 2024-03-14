#pragma once
#include <EngineCore/Actor.h>
#include "InGameValue.h"
#include "EnumClass.h"


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

	std::vector<UImageRenderer*> ScoreRenderer = std::vector<UImageRenderer*>();

private:

};

