#pragma once
#include <vector>
#include <string>

#include <EngineBase/EngineDebug.h>
#include <EngineBase/EngineMath.h>

#include "EnumClass.h"
#include "InGameValue.h"


// ���� :
class UPlayerInfoManager
{
public:
	// delete Function
	UPlayerInfoManager(const UPlayerInfoManager& _Other) = delete;
	UPlayerInfoManager(UPlayerInfoManager&& _Other) noexcept = delete;
	UPlayerInfoManager& operator=(const UPlayerInfoManager& _Other) = delete;
	UPlayerInfoManager& operator=(UPlayerInfoManager&& _Other) noexcept = delete;

	static UPlayerInfoManager& GetInst()
	{
		static UPlayerInfoManager Inst = UPlayerInfoManager();
		return Inst;
	}

	void SetAmountOfCoins(int _Amount)
	{
		AmountOfCoins = _Amount;
	}

	void AddAmountOfCoins(int _Amount)
	{
		AmountOfCoins += _Amount;
	}

	int GetAmountOfCoins() const
	{
		return AmountOfCoins;
	}

	void SetPlayerScore(int _Score)
	{
		PlayerScore = _Score;
	}

	void AddPlayerScore(int _Score)
	{
		PlayerScore += _Score;
	}

	int GetPlayerScore() const
	{
		return PlayerScore;
	}

	void SetPlayerLife(int _Life)
	{
		PlayerLife = _Life;
	}

	void AddPlayerLife(int _Value)
	{
		PlayerLife += _Value;
	}

	int GetPlayerLife() const
	{
		return PlayerLife;
	}

	void SetStageInfo(const std::vector<std::string>& _StageInfo)
	{
		if (2 == _StageInfo.size())
		{
			StageInfo = _StageInfo;
		}
		else
		{
			MsgBoxAssert("�������� ������ �ùٸ��� �ʽ��ϴ�.");
		}
	}

	const std::vector<std::string> GetStageInfo() const
	{
		return StageInfo;
	}

	void SetPlayerType(EMarioType _Type)
	{
		PlayerType = _Type;
	}

	EMarioType GetPlayerType() const
	{
		return PlayerType;
	}

	void SetPlayerColSize(FVector _ColSize)
	{
		PlayerColSize = _ColSize;
	}

	FVector GetPlayerColSize() const
	{
		return PlayerColSize;
	}

	void SetPrevStageLevel(std::string_view _StageLevel)
	{
		PrevStageLevel = _StageLevel;
	}

	std::string GetPrevStageLevel() const
	{
		return PrevStageLevel;
	}

	void ReSetInfo();

protected:

private:
	int PlayerLife = 3;
	int AmountOfCoins = 0;
	int PlayerScore = 0;
	std::vector<std::string> StageInfo = std::vector<std::string>({ "1", "1" });
	EMarioType PlayerType = EMarioType::Small;
	FVector PlayerColSize = FVector{ UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY };
	std::string PrevStageLevel = "";

	// constrcuter destructer
	UPlayerInfoManager();
	~UPlayerInfoManager();
};

