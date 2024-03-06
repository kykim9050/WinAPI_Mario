#pragma once
#include <vector>
#include <string>

// Ό³Έν :
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

	int GetAmountOfCoins() const
	{
		return AmountOfCoins;
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

