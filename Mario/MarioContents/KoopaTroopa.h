#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class AKoopaTroopa : public AActor
{
public:
	// constrcuter destructer
	AKoopaTroopa();
	~AKoopaTroopa();

	// delete Function
	AKoopaTroopa(const AKoopaTroopa& _Other) = delete;
	AKoopaTroopa(AKoopaTroopa&& _Other) noexcept = delete;
	AKoopaTroopa& operator=(const AKoopaTroopa& _Other) = delete;
	AKoopaTroopa& operator=(AKoopaTroopa&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

protected:

private:

};

