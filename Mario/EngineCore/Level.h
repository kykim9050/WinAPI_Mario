#pragma once
#include <EngineBase\NameObject.h>
#include <EngineBase\EngineMath.h>
#include <map>
#include <list>

class AActor;
class UCollision;
class UEngineCore;
class UImageRenderer;
// 설명 :
class ULevel : public UNameObject
{

	friend UEngineCore;
	friend UImageRenderer;
	friend UCollision;

public:
	// constrcuter destructer
	ULevel();
	~ULevel();

	// delete Function
	ULevel(const ULevel& _Other) = delete;
	ULevel(ULevel&& _Other) noexcept = delete;
	ULevel& operator=(const ULevel& _Other) = delete;
	ULevel& operator=(ULevel&& _Other) noexcept = delete;

	virtual void BeginPlay() {};
	virtual void Tick(float _DeltaTime) {};

	/// <summary>
	/// 레벨이 바뀌어서 처음으로 시작해야 하는 코드들을 나열
	/// 리소스 로드, 액터 초기화등 가능
	/// ULevel 클래스를 상속받으면 override로 사용 가능
	/// </summary>
	/// <param name="_PrevLevel"></param>
	virtual void LevelStart(ULevel* _PrevLevel) {};

	/// <summary>
	/// 현재 레벨이 끝나는 순간 실행되어야 하는 코드들을 나열
	/// 생성한 액터, 리스소 반환 등 가능
	/// ULevel 클래스를 상속받으면 override로 사용 가능
	/// </summary>
	/// <param name="_NextLevel"></param>
	virtual void LevelEnd(ULevel* _NextLevel) {};

	template<typename ActorType, typename EnumType>
	ActorType* SpawnActor(EnumType _Order)
	{
		return SpawnActor<ActorType>(static_cast<int>(_Order));
	}

	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

	/// <summary>
	/// 카메라 위치좌표를 지정하는 함수
	/// </summary>
	/// <param name="_CameraPos"></param>
	void SetCameraPos(FVector _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	/// <summary>
	/// 카메라의 위치에 인자로받은 위치좌표값을 더하는 함수
	/// </summary>
	/// <param name="_CameraPos"></param>
	void AddCameraPos(FVector _CameraPos)
	{
		CameraPos += _CameraPos;
	}

	/// <summary>
	/// 카메라의 위치 데이터를 받아오는 함수
	/// </summary>
	/// <returns></returns>
	FVector GetCameraPos()
	{
		return CameraPos;
	}

	void SetAllTimeScale(float _Scale)
	{
		for (std::pair<const int, float>& TimeScale : TimeScale)
		{
			TimeScale.second = _Scale;
		}
	}

	template<typename EnumType>
	void SetOtherTimeScale(EnumType _Value, float _Scale)
	{
		SetOtherTimeScale(static_cast<int>(_Value), _Scale);
	}

	void SetOtherTimeScale(int _Value, float _Scale)
	{
		for (std::pair<const int, float>& TimeScale : TimeScale)
		{
			if (TimeScale.first == _Value)
			{
				continue;
			}

			TimeScale.second = _Scale;
		}
	}

	template<typename EnumType>
	void SetTimeScale(EnumType _Value, float _Scale)
	{
		SetTimeScale(static_cast<int>(_Value), _Scale);
	}

	void SetTimeScale(int _Value, float _Scale)
	{
		TimeScale[_Value] = _Scale;
	}

protected:

private:
	std::map<int, std::list<AActor*>> AllActor;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);

	std::map<int, float> TimeScale;

	std::map<int, std::list<UImageRenderer*>> Renderers;

	std::map<int, std::list<UCollision*>> Collisions;

	/// <summary>
	/// 카메라 좌표 관련 맴버변수
	/// 특정 액터의 Pos가 변할때 함께 같은 값으로 변하면 해당 액터에 초점을 유지할 수 있다.
	/// ImageRenderer의 Render 함수에서 모든 Renderer의 좌표에서 카메라의 좌표를 빼고 있다.
	/// (좌표값이 이동하지 않는 Renderer들은 전부 camera만큼만 역으로 이동한다)
	/// </summary>
	FVector CameraPos = FVector::Zero;
};

