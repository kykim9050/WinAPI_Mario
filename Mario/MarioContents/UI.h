#pragma once
#include <EngineCore/Actor.h>
#include "PlayerMario.h"

// 설명 : UI는 플레이어와 독립되었지만 플레이어의 점수를 관여하고 있다.
// 플레이어는 사라지더라도 해당 UI점수는 남아있는 것으로 하고 새로운 레벨이 생성될 때 해당 UI점수와 랜더를 전달하도록 한다.
class AUI : public AActor
{
public:
	// constrcuter destructer
	AUI();
	~AUI();

	// delete Function
	AUI(const AUI& _Other) = delete;
	AUI(AUI&& _Other) noexcept = delete;
	AUI& operator=(const AUI& _Other) = delete;
	AUI& operator=(AUI&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void TimeCheck(float _DeltaTime);
	void TimeRenderUpdate();

	void NumberToAnimation(int _PrintNumber, int _AnimatingNum, const std::vector<UImageRenderer*>& _Renderer);
	void ScoreCheck();


private:
	UImageRenderer* PlayerUIRenderer = nullptr;
	std::vector<UImageRenderer*> TimeRenderer = std::vector<UImageRenderer*>();


	int TimeCount = 400;
	float TimeInterval = 1.0f;
	bool TimeChange = false;
	int PlayerScore = 0;
};

