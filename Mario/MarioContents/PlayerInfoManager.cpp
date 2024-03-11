#include "PlayerInfoManager.h"
#include "EnumClass.h"
#include "InGameValue.h"

int UPlayerInfoManager::PlayerLife = 3;
int UPlayerInfoManager::AmountOfCoins = 0;
int UPlayerInfoManager::PlayerScore = 0;
std::vector<std::string> UPlayerInfoManager::StageInfo = std::vector<std::string>({ "1", "1" });
EMarioType UPlayerInfoManager::PlayerType = EMarioType::Small;
FVector UPlayerInfoManager::PlayerColSize = FVector{ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY };
std::string UPlayerInfoManager::PrevStageLevel = "1-1";

UPlayerInfoManager::UPlayerInfoManager()
{
}

UPlayerInfoManager::~UPlayerInfoManager()
{
}


