#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>

class UWindowImage;
// Ό³Έν :
class UImageRenderer : public USceneComponent
{
public:
	// constrcuter destructer
	UImageRenderer();
	~UImageRenderer();

	// delete Function
	UImageRenderer(const UImageRenderer& _Other) = delete;
	UImageRenderer(UImageRenderer&& _Other) noexcept = delete;
	UImageRenderer& operator=(const UImageRenderer& _Other) = delete;
	UImageRenderer& operator=(UImageRenderer&& _Other) noexcept = delete;

	void SetOrder(int _Order) override;
	void Render(float _DeltaTime);
	
	void SetImage(std::string_view _Name, int _InfoIndex = 0);

	void SetImageIndex(int _InfoIndex)
	{
		InfoIndex = _InfoIndex;
	}

	void SetTransform(const FTransform& _Value)
	{
		USceneComponent::SetTransform(_Value);
	}

	void SetImageCuttingTransform(const FTransform& _Value)
	{
		ImageCuttingTransform = _Value;
	}

protected:
	void BeginPlay() override;

private:
	int InfoIndex = 0;
	UWindowImage* Image;
	FTransform ImageCuttingTransform;
};

