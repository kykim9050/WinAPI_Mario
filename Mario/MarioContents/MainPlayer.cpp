#include "MainPlayer.h"
#include "PlayerMario.h"

UMainPlayer::UMainPlayer()
{
	Player = APlayerMario::GetMainPlayer();
}

UMainPlayer::~UMainPlayer()
{
}


