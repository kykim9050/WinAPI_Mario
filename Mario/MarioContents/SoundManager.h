#pragma once

// Ό³Έν :
class USoundManager
{
public:
	
	static USoundManager& GetInst()
	{
		static USoundManager Inst = USoundManager();
		return Inst;
	}

	// delete Function
	USoundManager(const USoundManager& _Other) = delete;
	USoundManager(USoundManager&& _Other) noexcept = delete;
	USoundManager& operator=(const USoundManager& _Other) = delete;
	USoundManager& operator=(USoundManager&& _Other) noexcept = delete;

protected:

private:
	USoundManager();
	~USoundManager();
};

