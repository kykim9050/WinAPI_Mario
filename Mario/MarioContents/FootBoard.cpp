#include "FootBoard.h"

AFootBoard::AFootBoard()
{
}

AFootBoard::~AFootBoard()
{
}

void AFootBoard::BeginPlay()
{
	UStateUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	Renderer->SetImage("FootBoard.png");

	FVector FootBoardScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {FootBoardScale.iX() * UInGameValue::WindowSizeMulValue, FootBoardScale.iY() * UInGameValue::WindowSizeMulValue} });


	BodyCollision = CreateCollision(ECollisionOrder::BlockTop);
	BodyCollision->SetTransform({ { 0,0 }, { FootBoardScale.iX() * UInGameValue::WindowSizeMulValue, FootBoardScale.iY() * UInGameValue::WindowSizeMulValue } });
	BodyCollision->SetColType(ECollisionType::Rect);

	//SetActorState(EActorState::Idle);
}

void AFootBoard::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}
