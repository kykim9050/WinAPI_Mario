#include "PlayerMario.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>
#include <EngineBase/EngineMath.h>

APlayerMario::APlayerMario()
{
}

APlayerMario::~APlayerMario()
{
}

void APlayerMario::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* MarioRenderer = CreateImageRenderer(static_cast<int>(StageRenderOrder::Mario));

	MarioRenderer->SetImage("Mario_Stop_Right.png");
	MarioRenderer->SetTransform({ {300, 300}, {200, 200} });

}

void APlayerMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	

	if (EngineInput::IsPress(VK_LEFT))
	{
		AddActorLocation(FVector::Left * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Left * PVelocity * _DeltaTime);
	}

	if (EngineInput::IsPress(VK_RIGHT))
	{
		AddActorLocation(FVector::Right * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Right * PVelocity * _DeltaTime);
	}

	if (EngineInput::IsPress(VK_UP))
	{
		AddActorLocation(FVector::Up * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Up * PVelocity * _DeltaTime);
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
		AddActorLocation(FVector::Down * PVelocity * _DeltaTime);
		GetWorld()->AddCameraPos(FVector::Down * PVelocity * _DeltaTime);
	}

}