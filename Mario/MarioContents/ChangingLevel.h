#pragma once
#include <EngineCore/Level.h>

// Ό³Έν :
class UChangingLevel : public ULevel
{
public:
	// constrcuter destructer
	UChangingLevel();
	~UChangingLevel();

	// delete Function
	UChangingLevel(const UChangingLevel& _Other) = delete;
	UChangingLevel(UChangingLevel&& _Other) noexcept = delete;
	UChangingLevel& operator=(const UChangingLevel& _Other) = delete;
	UChangingLevel& operator=(UChangingLevel&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void LevelEnd(ULevel* _NextLevel) override;

private:

};

