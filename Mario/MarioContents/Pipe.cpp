#include "Pipe.h"

APipe::APipe()
{
}

APipe::~APipe()
{
}

void APipe::BeginPlay()
{
	AStructureUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::MonsterHideStructure));
	Renderer->SetImage("Pipe.png");
	FVector PipeScale = Renderer->GetImage()->GetScale();
	Renderer->SetTransform({ {0,0}, {PipeScale.iX(), PipeScale.iY()} });
}


void APipe::Tick(float _DeltaTime)
{
	AStructureUnit::Tick(_DeltaTime);
}