#pragma once
#include <EngineCore/Actor.h>

// Ό³Έν :
class ATextUnit : public AActor
{
public:
	// constrcuter destructer
	ATextUnit();
	~ATextUnit();

	// delete Function
	ATextUnit(const ATextUnit& _Other) = delete;
	ATextUnit(ATextUnit&& _Other) noexcept = delete;
	ATextUnit& operator=(const ATextUnit& _Other) = delete;
	ATextUnit& operator=(ATextUnit&& _Other) noexcept = delete;

	void SetScoreAnimation(int _ScoreValue);
	void SetLocation(FVector _InitPos);
	void SetSpeed(float _Speed)
	{
		RisingSpeed = _Speed;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void MoveUpdate(float _Deltatime, float _Speed);

private:
	float GetRisingSpeed() const
	{
		return RisingSpeed;
	}

	UImageRenderer* TextRenderer = nullptr;
	float RisingSpeed = 200.0f;
};

