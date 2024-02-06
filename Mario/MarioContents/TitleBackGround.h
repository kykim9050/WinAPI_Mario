#pragma once
#include <EngineCore/Actor.h>


// Ό³Έν :
class ATitleBackGround : public AActor
{
public:
	// constrcuter destructer
	ATitleBackGround();
	~ATitleBackGround();

	// delete Function
	ATitleBackGround(const ATitleBackGround& _Other) = delete;
	ATitleBackGround(ATitleBackGround&& _Other) noexcept = delete;
	ATitleBackGround& operator=(const ATitleBackGround& _Other) = delete;
	ATitleBackGround& operator=(ATitleBackGround&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:

};

