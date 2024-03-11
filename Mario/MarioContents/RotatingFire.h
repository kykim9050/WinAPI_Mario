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


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	class AFireObstacle
	{
		friend ARotatingFire;
	public:
		AFireObstacle();
		~AFireObstacle();
	protected:

	private:
		UCollision* ObstacleCol = nullptr;
		UImageRenderer* ObstacleRenderer = nullptr;
	};



};

