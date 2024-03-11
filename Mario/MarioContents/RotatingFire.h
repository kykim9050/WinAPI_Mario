#pragma once
#include "MovingObjectUnit.h"


class UCollision;
class UImageRenderer;

// Ό³Έν :
class ARotatingFire : public AMovingObjectUnit
{
public:
	// constrcuter destructer
	ARotatingFire();
	~ARotatingFire();

	// delete Function
	ARotatingFire(const ARotatingFire& _Other) = delete;
	ARotatingFire(ARotatingFire&& _Other) noexcept = delete;
	ARotatingFire& operator=(const ARotatingFire& _Other) = delete;
	ARotatingFire& operator=(ARotatingFire&& _Other) noexcept = delete;

	class AFireObstacle : public AActor
	{
		friend ARotatingFire;
	public:
		AFireObstacle() {}
		~AFireObstacle() {}


	protected:

	private:
		UImageRenderer* ObstacleRenderer = nullptr;
		UCollision* ObstacleCol = nullptr;
		
		void CreateFireObstacle();
	};

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void FirstInit() override;
	void Idle(float _DeltaTime) override;
	void Rotating(float _DeltaTime) override;

private:
	std::vector<AFireObstacle*> RotatingFire = std::vector<AFireObstacle*>();
	int ObstacleNum = 6;
	float Angle = 0.0f;
	float RotatingSpeed = 120.0f;
};

