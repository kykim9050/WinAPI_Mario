#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>
#include <map>

class UAnimationInfo
{
public:
	// 애니메이션을 구성할때 이미지는 1장
	UWindowImage* Image = nullptr;
	std::string Name;
	int CurFrame = 0;
	float CurTime = 0.0f;
	bool Loop = false;
	bool IsEnd = false;
	std::vector<float> Times;
	std::vector<int> Indexs;

	int Update(float _DeltaTime);
};

class UWindowImage;
// 설명 :
class UImageRenderer : public USceneComponent
{
public:

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

	/// <summary>
	/// 이미지를 조합하여 애니메이션을 만드는 함수.
	/// 여러개의 이미지가 모여있는 리소스 이미지에서 특정 시점과 종점의 idx를 지정하여 순서대로 진행되는 애니메이션을 만들 수 있다.
	/// </summary>
	/// <param name="_AnimationName"></param>
	/// <param name="_ImageName"></param>
	/// <param name="_Start"></param>
	/// <param name="_End"></param>
	/// <param name="_Inter"></param>
	/// <param name="_Loop"></param>
	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		int _Start,
		int _End,
		float _Inter,
		bool _Loop = true
	);

	/// <summary>
	/// 이미지를 조합하여 애니메이션을 만드는 함수.
	/// 여러개의 이미지가 모여있는 리소스 이미지의 Index(순서)를 직접 설정하여 원하는 순서의 애니메이션을 지정할 수 있다.
	/// </summary>
	/// <param name="_AnimationName"></param>
	/// <param name="_ImageName"></param>
	/// <param name="_Indexs"></param>
	/// <param name="_Inter"></param>
	/// <param name="_Loop"></param>
	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _ImageName,
		std::vector<int> _Indexs,
		float _Inter,
		bool _Loop = true
	);

	/// <summary>
	/// 애니메이션을 변경하는 함수.
	/// _IsForce는 같은 종류의 애니메이션도 강제로 idx0부터 실행시킬지를 정할 수 있는 인자
	/// 애니메이션 변경 시, 대칭되는 애니메이션이 있다면 이미지도 대칭일테니 _StartIndex, _Time인자에 대응되는 값을 대입할 것
	/// 대칭되는 애니메이션이 아니라면 디폴트인자로 넘길 것
	/// </summary>
	/// <param name="_AnimationName"></param>
	/// <param name="_IsForce"></param>
	/// <param name="_StartIndex"></param>
	/// <param name="_Time"></param>
	void ChangeAnimation(std::string_view _AnimationName, bool _IsForce = false, int _StartIndex = 0, float _Time = -1.0f);
	void AnimationReset();

	void SetAngle(float _Angle)
	{
		Angle = _Angle;
	}

	void SetTransColor(Color8Bit _Color)
	{
		TransColor = _Color;
	}

	void SetAlpha(float _Alpha)
	{
		if (0.0f >= _Alpha)
		{
			_Alpha = 0.0f;
		}

		if (1.0f <= _Alpha)
		{
			_Alpha = 1.0f;
		}

		TransColor.A = static_cast<char>(_Alpha * 255.0f);
	}

	UWindowImage* GetImage() const
	{
		return Image;
	}

	/// <summary>
	/// Camera 효과의 영향을 받지 않게 하는 함수
	/// </summary>
	void CameraEffectOff()
	{
		CameraEffect = false;
	}

	/// <summary>
	/// 지정해놓은 애니메이션의 한 사이클이 끝났을 때, true를 반환한다.
	/// </summary>
	/// <returns></returns>
	bool IsCurAnimationEnd() const
	{
		return CurAnimation->IsEnd;
	}

	/// <summary>
	/// UAnimationInfo의 맴버 vector 자료구조 Indexs의 idx 값을 가져오는 함수
	/// Indexs의 idx에 매칭되는 실제 값은 리소스 이미지(PNG등)의 실제 이미지 프레임 번호이다.
	/// </summary>
	/// <returns></returns>
	int GetCurAnimationFrame() const
	{
		return CurAnimation->CurFrame;
	}

	/// <summary>
	/// 현재의 애니메이션에서 indexs의 값인 이미지 프레임 번호를 가져오는 함수
	/// </summary>
	/// <returns></returns>
	int GetCurAnimationImageFrame() const
	{
		const std::vector<int>& Indexs = CurAnimation->Indexs;
		return Indexs[CurAnimation->CurFrame];
	}

	/// <summary>
	/// 애니메이션 실행 중 _DeltaTime을 뺀 현재 시간
	/// DeltaTime을 계속 빼다보면 0보다 작아질 때 해당되는 Frame에 대한 시간 값을 가져온다.
	/// </summary>
	/// <returns></returns>
	float GetCurAnimationTime() const
	{
		return CurAnimation->CurTime;
	}

	UAnimationInfo* GetCurAnimation() const
	{
		return CurAnimation;
	}

	void TextRender(float _DeltaTime);
	void ImageRender(float _DeltaTime);

	void SetText(std::string_view _Text)
	{
		Text = _Text;
	}
	void SetFont(std::string_view _Font)
	{
		Font = _Font;
	}
	void SetTextSize(float _Value)
	{
		Size = _Value;
	}
	void SetTextColor(Color8Bit _Color, Color8Bit _Color2 = Color8Bit::White)
	{
		TextColor = _Color;
		TextColor2 = _Color2;
	}

	void SetCameraRatio(float _Ratio)
	{
		CameraRatio = _Ratio;
	}

	FTransform GetRenderTransForm();

	// Text 효과
	void SetTextEffect(int _Effect = 0)
	{
		TextEffect = _Effect;
	}

protected:
	void BeginPlay() override;

private:
	int InfoIndex = 0;
	UWindowImage* Image = nullptr;
	FTransform ImageCuttingTransform;
	Color8Bit TransColor;

	bool CameraEffect = true;
	float CameraRatio = 1.0f;

	std::map<std::string, UAnimationInfo> AnimationInfos;
	UAnimationInfo* CurAnimation = nullptr;

	float Angle = 0.0f;

	std::string Text = "";
	std::string Font = "궁서";
	float Size = 10.0f;
	Color8Bit TextColor = Color8Bit::BlackA;

	Color8Bit TextColor2 = Color8Bit::BlackA; 
	int TextEffect = 0;
	// Default : 0, 
	// Bold & Italic : 1, (custom)
	// Bold : 2,
	// ...
};

