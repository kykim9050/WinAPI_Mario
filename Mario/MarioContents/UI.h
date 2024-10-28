#pragma once
#include <EngineCore/Actor.h>
#include "PlayerMario.h"

// ���� : UI�� �÷��̾�� �����Ǿ����� �÷��̾��� ������ �����ϰ� �ִ�.
// �÷��̾�� ��������� �ش� UI������ �����ִ� ������ �ϰ� ���ο� ������ ������ �� �ش� UI������ ������ �����ϵ��� �Ѵ�.
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

