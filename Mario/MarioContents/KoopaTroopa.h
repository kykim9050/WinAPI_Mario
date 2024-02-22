#pragma once
#include "StateUnit.h"
#include "EnumClass.h"
#include "InGameValue.h"
#include "ContentsFunction.h"

// Ό³Έν :
class AKoopaTroopa : public UStateUnit
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

	void StateUpdate(float _DeltaTime) override;

	void Move(float _DeltaTime) override;

	void ResultMovementUpdate(float _DeltaTime) override;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	bool KillPlayer = false;
};

