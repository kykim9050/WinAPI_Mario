#include "MainPlayer.h"
#include "PlayerMario.h"

UMainPlayer::UMainPlayer()
{
	Player = APlayerMario::GetMainPlayer();

	if (nullptr == Player)
	{
		MsgBoxAssert("플레이어가 존재하지 않습니다.");
	}
}

UMainPlayer::~UMainPlayer()
{
}


