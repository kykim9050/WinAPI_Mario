#include "PlayerInfoManager.h"
#include "EnumClass.h"
#include "InGameValue.h"

int UPlayerInfoManager::PlayerLife = 3;
int UPlayerInfoManager::AmountOfCoins = 0;
int UPlayerInfoManager::PlayerScore = 0;
std::vector<std::string> UPlayerInfoManager::StageInfo = std::vector<std::string>({ "1", "1" });
EMarioType UPlayerInfoManager::PlayerType = EMarioType::Small;
FVector UPlayerInfoManager::PlayerColSize = FVector{ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY };
std::string UPlayerInfoManager::PrevStageLevel = "";

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
