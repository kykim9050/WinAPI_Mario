#pragma once
#include <vector>
#include <string>
#include <EngineBase/EngineDebug.h>

// 설명 :
class UPlayerScoreManager
{
public:
	// delete Function
	UPlayerScoreManager(const UPlayerScoreManager& _Other) = delete;
	UPlayerScoreManager(UPlayerScoreManager&& _Other) noexcept = delete;
	UPlayerScoreManager& operator=(const UPlayerScoreManager& _Other) = delete;
	UPlayerScoreManager& operator=(UPlayerScoreManager&& _Other) noexcept = delete;

	static UPlayerScoreManager& GetInst()
	{
		static UPlayerScoreManager Inst = UPlayerScoreManager();
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

protected:

private:
	static int PlayerLife;
	static int AmountOfCoins;
	static int PlayerScore;
	static std::vector<std::string> StageInfo;

	// constrcuter destructer
	UPlayerScoreManager();
	~UPlayerScoreManager();
};

