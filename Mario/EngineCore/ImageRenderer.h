#pragma once
#include "SceneComponent.h"
#include <EnginePlatform\WindowImage.h>
#include <map>

class UAnimationInfo
{
public:
	// �ִϸ��̼��� �����Ҷ� �̹����� 1��
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
// ���� :
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
	/// �̹����� �����Ͽ� �ִϸ��̼��� ����� �Լ�.
	/// �������� �̹����� ���ִ� ���ҽ� �̹������� Ư�� ������ ������ idx�� �����Ͽ� ������� ����Ǵ� �ִϸ��̼��� ���� �� �ִ�.
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
	/// �̹����� �����Ͽ� �ִϸ��̼��� ����� �Լ�.
	/// �������� �̹����� ���ִ� ���ҽ� �̹����� Index(����)�� ���� �����Ͽ� ���ϴ� ������ �ִϸ��̼��� ������ �� �ִ�.
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
	/// �ִϸ��̼��� �����ϴ� �Լ�.
	/// _IsForce�� ���� ������ �ִϸ��̼ǵ� ������ idx0���� �����ų���� ���� �� �ִ� ����
	/// �ִϸ��̼� ���� ��, ��Ī�Ǵ� �ִϸ��̼��� �ִٸ� �̹����� ��Ī���״� _StartIndex, _Time���ڿ� �����Ǵ� ���� ������ ��
	/// ��Ī�Ǵ� �ִϸ��̼��� �ƴ϶�� ����Ʈ���ڷ� �ѱ� ��
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
	/// Camera ȿ���� ������ ���� �ʰ� �ϴ� �Լ�
	/// </summary>
	void CameraEffectOff()
	{
		CameraEffect = false;
	}

	/// <summary>
	/// �����س��� �ִϸ��̼��� �� ����Ŭ�� ������ ��, true�� ��ȯ�Ѵ�.
	/// </summary>
	/// <returns></returns>
	bool IsCurAnimationEnd() const
	{
		return CurAnimation->IsEnd;
	}

	/// <summary>
	/// UAnimationInfo�� �ɹ� vector �ڷᱸ�� Indexs�� idx ���� �������� �Լ�
	/// Indexs�� idx�� ��Ī�Ǵ� ���� ���� ���ҽ� �̹���(PNG��)�� ���� �̹��� ������ ��ȣ�̴�.
	/// </summary>
	/// <returns></returns>
	int GetCurAnimationFrame() const
	{
		return CurAnimation->CurFrame;
	}

	/// <summary>
	/// ������ �ִϸ��̼ǿ��� indexs�� ���� �̹��� ������ ��ȣ�� �������� �Լ�
	/// </summary>
	/// <returns></returns>
	int GetCurAnimationImageFrame() const
	{
		const std::vector<int>& Indexs = CurAnimation->Indexs;
		return Indexs[CurAnimation->CurFrame];
	}

	/// <summary>
	/// �ִϸ��̼� ���� �� _DeltaTime�� �� ���� �ð�
	/// DeltaTime�� ��� ���ٺ��� 0���� �۾��� �� �ش�Ǵ� Frame�� ���� �ð� ���� �����´�.
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

	// Text ȿ��
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
	std::string Font = "�ü�";
	float Size = 10.0f;
	Color8Bit TextColor = Color8Bit::BlackA;

	Color8Bit TextColor2 = Color8Bit::BlackA; 
	int TextEffect = 0;
	// Default : 0, 
	// Bold & Italic : 1, (custom)
	// Bold : 2,
	// ...
};

