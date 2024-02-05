#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class UTitleBackGround : public AActor
{
public:
	// constrcuter destructer
	UTitleBackGround();
	~UTitleBackGround();

	// delete Function
	UTitleBackGround(const UTitleBackGround& _Other) = delete;
	UTitleBackGround(UTitleBackGround&& _Other) noexcept = delete;
	UTitleBackGround& operator=(const UTitleBackGround& _Other) = delete;
	UTitleBackGround& operator=(UTitleBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

