#include "DebugLevel.h"
#include <EnginePlatform/EngineInput.h>
#include "PlayerMario.h"

UDebugLevel::UDebugLevel()
{
}

UDebugLevel::~UDebugLevel()
{
}

void UDebugLevel::BeginPlay()
{
	ULevel::BeginPlay();
}

void UDebugLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);

	if (true == UEngineInput::IsDown(VK_F3))
	{
		APlayerMario* Player = APlayerMario::GetMainPlayer();

		if (nullptr == Player)
		{
			UEngineDebug::OutPutDebugText("Player가 없습니다.");
			return;
		}

		if (Player->GetBodyCollision()->IsActive())
		{
			Player->GetBodyCollision()->SetActive(false);
			Player->GetRenderer()->SetAlpha(0.5f);
		}
		else
		{
			Player->GetBodyCollision()->SetActive(true);
			Player->GetRenderer()->SetAlpha(1.0f);
		}
	}

	if (true == UEngineInput::IsDown('3'))
	{
		APlayerMario* Player = APlayerMario::GetMainPlayer();

		if (nullptr == Player)
		{
			UEngineDebug::OutPutDebugText("Player가 없습니다.");
			return;
		}

		Player->StateChange(EActorState::MarioGrowUp);
	}

	if (true == UEngineInput::IsDown('4'))
	{
		APlayerMario* Player = APlayerMario::GetMainPlayer();

		if (nullptr == Player)
		{
			UEngineDebug::OutPutDebugText("Player가 없습니다.");
			return;
		}

		Player->StateChange(EActorState::FireMario);
	}

	if (true == UEngineInput::IsDown('5'))
	{
		APlayerMario* Player = APlayerMario::GetMainPlayer();

		if (nullptr == Player)
		{
			UEngineDebug::OutPutDebugText("Player가 없습니다.");
			return;
		}

		if (EMarioType::Small == Player->GetMarioType())
		{
			return;
		}

		Player->StateChange(EActorState::GetHit);
	}


	if (true == UEngineInput::IsDown(VK_F4))
	{
		if (false == GetTimeStop())
		{
			TimeStopOnOff();
			SetAllTimeScale(0.0f);
			SetTimeScale(EActorType::Player, 1.0f);
			return;
		}
		else {
			TimeStopOnOff();
			SetAllTimeScale(1.0f);
			return;
		}
	}
}

