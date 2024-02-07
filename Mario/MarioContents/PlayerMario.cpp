#include "PlayerMario.h"
#include "EnumClass.h"
#include <EnginePlatform/EngineInput.h>

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

	}

	if (EngineInput::IsPress(VK_RIGHT))
	{

	}

	if (EngineInput::IsPress(VK_UP))
	{
	
	}

	if (EngineInput::IsPress(VK_DOWN))
	{
	
	}

}