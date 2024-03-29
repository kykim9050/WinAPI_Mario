#pragma once
#include "StructureUnit.h"

// ���� :
class ACastle : public AStructureUnit
{
public:
	// constrcuter destructer
	ACastle();
	~ACastle();

	// delete Function
	ACastle(const ACastle& _Other) = delete;
	ACastle(ACastle&& _Other) noexcept = delete;
	ACastle& operator=(const ACastle& _Other) = delete;
	ACastle& operator=(ACastle&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void CollisionCheck() override;
	void Appear(float _DeltaTime) override;
	
	void FlagRisingCheck();


private:
	UImageRenderer* FlagRenderer = nullptr;
	int ActorBaseGateColXPos = 16;
	int ActorBaseCastleFlagXPos = 0;
	int ActorBaseCastleFlagYPos = -20 * UInGameValue::WindowSizeMulValue;
	int FlagRisingCutline = -48 * UInGameValue::WindowSizeMulValue;
	bool FlagRising = false;
};

