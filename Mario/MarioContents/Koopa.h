#pragma once
#include "MonsterUnit.h"

// ���� :
class AKoopa : public AMonsterUnit
{
public:
	// constrcuter destructer
	AKoopa();
	~AKoopa();

	// delete Function
	AKoopa(const AKoopa& _Other) = delete;
	AKoopa(AKoopa&& _Other) noexcept = delete;
	AKoopa& operator=(const AKoopa& _Other) = delete;
	AKoopa& operator=(AKoopa&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};
