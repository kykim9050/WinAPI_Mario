#include "PlayerMario.h"
#include "EnumClass.h"

APlayerMario::APlayerMario()
{
}

APlayerMario::~APlayerMario()
{
}

void APlayerMario::BeginPlay()
{
	AActor::BeginPlay();

	//UImageRenderer* MarioRenderer = CreateImageRenderer(static_cast<int>(StageRenderOrder::Mario));

}

void APlayerMario::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

}