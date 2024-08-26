#include "PlayerInfoManager.h"


UPlayerInfoManager::UPlayerInfoManager()
{
}

UPlayerInfoManager::~UPlayerInfoManager()
{
}

void UPlayerInfoManager::ReSetInfo()
{
	SetPlayerLife(3);
	SetAmountOfCoins(0);
	SetPlayerScore(0);
	SetStageInfo(std::vector<std::string>({ "1", "1" }));
	SetPlayerType(EMarioType::Small);
	SetPlayerColSize(FVector{ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY });
	SetPrevStageLevel("");
}
