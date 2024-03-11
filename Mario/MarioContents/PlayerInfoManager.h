#pragma once
#include <vector>
#include <string>
#include <EngineBase/EngineDebug.h>
#include "EnumClass.h"
#include <EngineBase/EngineMath.h>

// 설명 :
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
			MsgBoxAssert("스테이지 정보가 올바르지 않습니다.");
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

protected:

private:
	static int PlayerLife;
	static int AmountOfCoins;
	static int PlayerScore;
	static std::vector<std::string> StageInfo;
	static EMarioType PlayerType;
	static FVector PlayerColSize;
	static std::string PrevStageLevel;

	// constrcuter destructer
	UPlayerInfoManager();
	~UPlayerInfoManager();
};

