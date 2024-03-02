﻿#include "Mushroom.h"
#include "PlayerMario.h"

AMushroom::AMushroom()
{
}

AMushroom::~AMushroom()
{
}

void AMushroom::BeginPlay()
{
	AItemUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Items.png");

	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::ItemsImageXValue * UInGameValue::WindowSizeMulValue, ItemScale.iY() / UInGameValue::ItemsImageYValue * UInGameValue::WindowSizeMulValue} });
	Renderer->CreateAnimation("Mushroom", "Items.png", 0, 0, 0.1f, true);
	Renderer->ChangeAnimation("Mushroom");

	BodyCollision = CreateCollision(ECollisionOrder::Mushroom);
	BodyCollision->SetTransform({ { 0, 0}, { UInGameValue::MushroomCollisionScaleX, UInGameValue::MushroomCollisionScaleY} });
	BodyCollision->SetColType(ECollisionType::Rect);

	SetActorState(EActorState::FirstInit);
}

void AMushroom::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}

void AMushroom::FirstInit(float _DeltaTime)
{
	AItemUnit::FirstInit(_DeltaTime);

	BodyCollision->ActiveOff();
	Renderer->ActiveOff();

	StateChange(EActorState::Idle);
}


void AMushroom::MoveStart()
{
	BodyCollision->ActiveOn();

}


void AMushroom::Appear(float _DeltaTime)
{
	if (GetActorLocation().Y < InitPos.Y - (UInGameValue::BlockCollisionScaleY / 2) - (UInGameValue::MushroomCollisionScaleY / 2))
	{
		SetActorLocation({GetActorLocation().X, GetActorLocation().Y });
		StateChange(EActorState::Move);
	}

	AddActorLocation(FVector::Up * 60.0f * _DeltaTime);
}

void AMushroom::Move(float _DeltaTime)
{
	AddActorLocation(FVector::Right * 100.0f * _DeltaTime);
}



void AMushroom::CollisionCheck()
{
	std::vector<UCollision*> Result = std::vector<UCollision*>();

	APlayerMario* Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		Player->EattingMushroom();
		CollisionStateChange(ECollisionState::GetHit);
		return;
	}
}