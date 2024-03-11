#include "RotatingFire.h"


void ARotatingFire::AFireObstacle::CreateFireObstacle()
{
	ObstacleRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::AttackableTrap));
	ObstacleRenderer->SetImage("FireBall.png");

	FVector FireObstacleScale = ObstacleRenderer->GetImage()->GetScale();

	ObstacleRenderer->SetTransform({ {0,0}, {FireObstacleScale.iX() / UInGameValue::FireBallImageXValue * UInGameValue::WindowSizeMulValue, FireObstacleScale.iY() / UInGameValue::FireBallImageYValue * UInGameValue::WindowSizeMulValue} });
	ObstacleRenderer->CreateAnimation("Fire_Rotating", "FireBall.png", 0, 3, 0.3f, true);
	ObstacleRenderer->ChangeAnimation("Fire_Rotating");

	ObstacleCol = CreateCollision(ECollisionOrder::AttackableTrap);
	ObstacleCol->SetTransform({ {0,0}, {8 * UInGameValue::WindowSizeMulValue, 8 * UInGameValue::WindowSizeMulValue} });
	ObstacleCol->SetColType(ECollisionType::CirCle);
}

ARotatingFire::ARotatingFire()
{
}

ARotatingFire::~ARotatingFire()
{
}

void ARotatingFire::BeginPlay()
{
	AMovingObjectUnit::BeginPlay();

	for (int i = 0; i < 6; i++)
	{
		AFireObstacle* obstacle = GetWorld()->SpawnActor<AFireObstacle>(static_cast<int>(EActorType::AttackableTrap));
		obstacle->CreateFireObstacle();
		// 위치 지정은 BeginPlay 실행하고 난 뒤에 해야겠다 FirstInit에서
		obstacle->SetActorLocation({ 500 , 500 + 24 * i});
		RotatingFire.push_back(obstacle);
	}

}

void ARotatingFire::Tick(float _DeltaTime)
{
	AMovingObjectUnit::Tick(_DeltaTime);
}


