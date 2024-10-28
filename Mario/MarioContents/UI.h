#pragma once
#include <EngineCore/Actor.h>

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

private:
	UImageRenderer* PlayerUIRenderer = nullptr;
};

