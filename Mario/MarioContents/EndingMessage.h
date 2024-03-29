#pragma once
#include <EngineCore/Actor.h>

// ���� :
class AEndingMessage : public AActor
{
public:
	// constrcuter destructer
	AEndingMessage();
	~AEndingMessage();

	// delete Function
	AEndingMessage(const AEndingMessage& _Other) = delete;
	AEndingMessage(AEndingMessage&& _Other) noexcept = delete;
	AEndingMessage& operator=(const AEndingMessage& _Other) = delete;
	AEndingMessage& operator=(AEndingMessage&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	const int MessageNum = 5;
	int CurMessageNum = MessageNum;
	float MessageOutPutIntervalTime = 1.0f;
	UImageRenderer* MessageHideRenderer = nullptr;
	FVector MessageHideScale;

	int MessageVal = 1;
};

