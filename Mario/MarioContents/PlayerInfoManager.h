#pragma once
#include <vector>
#include <string>
#include <EngineBase/EngineDebug.h>

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

protected:

private:
	static int PlayerLife;
	static int AmountOfCoins;
	static int PlayerScore;
	static std::vector<std::string> StageInfo;

	// constrcuter destructer
	UPlayerInfoManager();
	~UPlayerInfoManager();
};

