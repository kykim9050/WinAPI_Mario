#pragma once
#include "CreateLevel.h"


class ABackGroundMap;
class UCollisionMap;
class APlayerMario;
class AUI;
// ���� :
class U1_4StageLevel : public UCreateLevel
{
public:
	// constrcuter destructer
	U1_4StageLevel();
	~U1_4StageLevel();

	// delete Function
	U1_4StageLevel(const U1_4StageLevel& _Other) = delete;
	U1_4StageLevel(U1_4StageLevel&& _Other) noexcept = delete;
	U1_4StageLevel& operator=(const U1_4StageLevel& _Other) = delete;
	U1_4StageLevel& operator=(U1_4StageLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	ABackGroundMap* Map = nullptr;
	UCollisionMap* ColMap = nullptr;
	APlayerMario* Mario = nullptr;
	AUI* PlayerUI = nullptr;
};

