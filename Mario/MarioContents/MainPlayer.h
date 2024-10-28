#pragma once


class APlayerMario;

// ���� :
class UMainPlayer
{
public:
	// constrcuter destructer
	UMainPlayer();
	~UMainPlayer();

	// delete Function
	UMainPlayer(const UMainPlayer& _Other) = delete;
	UMainPlayer(UMainPlayer&& _Other) noexcept = delete;
	UMainPlayer& operator=(const UMainPlayer& _Other) = delete;
	UMainPlayer& operator=(UMainPlayer&& _Other) noexcept = delete;

protected:

	APlayerMario* GetPlayer()
	{
		return Player;
	}

private:
	APlayerMario* Player = nullptr;

};

