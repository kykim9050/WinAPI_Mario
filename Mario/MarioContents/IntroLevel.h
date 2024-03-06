#pragma once
#include <EngineCore/Level.h>
#include "EnumClass.h"
#include "InGameValue.h"

// Ό³Έν :

class ABackGroundMap;

class UIntroLevel : public ULevel
{
public:
	// constrcuter destructer
	UIntroLevel();
	~UIntroLevel();

	// delete Function
	UIntroLevel(const UIntroLevel& _Other) = delete;
	UIntroLevel(UIntroLevel&& _Other) noexcept = delete;
	UIntroLevel& operator=(const UIntroLevel& _Other) = delete;
	UIntroLevel& operator=(UIntroLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;


private:
	ABackGroundMap* Map = nullptr;

};

