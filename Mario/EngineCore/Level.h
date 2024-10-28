#pragma once
#include <EngineBase\NameObject.h>
#include <EngineBase\EngineMath.h>
#include <map>
#include <list>

class AActor;
class UEngineCore;
class UImageRenderer;
// ���� :
class ULevel : public UNameObject
{

	friend UEngineCore;
	friend UImageRenderer;

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
	/// ������ �ٲ� ó������ �����ؾ� �ϴ� �ڵ���� ����
	/// ���ҽ� �ε�, ���� �ʱ�ȭ�� ����
	/// ULevel Ŭ������ ��ӹ����� override�� ��� ����
	/// </summary>
	/// <param name="_PrevLevel"></param>
	virtual void LevelStart(ULevel* _PrevLevel) {};

	/// <summary>
	/// ���� ������ ������ ���� ����Ǿ�� �ϴ� �ڵ���� ����
	/// ������ ����, ������ ��ȯ �� ����
	/// ULevel Ŭ������ ��ӹ����� override�� ��� ����
	/// </summary>
	/// <param name="_NextLevel"></param>
	virtual void LevelEnd(ULevel* _NextLevel) {};

	template<typename ActorType>
	ActorType* SpawnActor(int _Order = 0)
	{
		ActorType* NewActor = new ActorType();
		ActorInit(NewActor);
		AllActor[_Order].push_back(NewActor);
		return NewActor;
	}

	/// <summary>
	/// ī�޶� ��ġ��ǥ�� �����ϴ� �Լ�
	/// </summary>
	/// <param name="_CameraPos"></param>
	void SetCameraPos(FVector _CameraPos)
	{
		CameraPos = _CameraPos;
	}

	/// <summary>
	/// ī�޶��� ��ġ�� ���ڷι��� ��ġ��ǥ���� ���ϴ� �Լ�
	/// </summary>
	/// <param name="_CameraPos"></param>
	void AddCameraPos(FVector _CameraPos)
	{
		CameraPos += _CameraPos;
	}

	/// <summary>
	/// ī�޶��� ��ġ �����͸� �޾ƿ��� �Լ�
	/// </summary>
	/// <returns></returns>
	FVector GetCameraPos()
	{
		return CameraPos;
	}


protected:

private:
	std::map<int, std::list<AActor*>> AllActor;

	void ActorInit(AActor* _NewActor);
	void LevelTick(float _DeltaTime);
	void LevelRender(float _DeltaTime);
	void LevelRelease(float _DeltaTime);

	std::map<int, std::list<UImageRenderer*>> Renderers;

	/// <summary>
	/// ī�޶� ��ǥ ���� �ɹ�����
	/// Ư�� ������ Pos�� ���Ҷ� �Բ� ���� ������ ���ϸ� �ش� ���Ϳ� ������ ������ �� �ִ�.
	/// ImageRenderer�� Render �Լ����� ��� Renderer�� ��ǥ���� ī�޶��� ��ǥ�� ���� �ִ�.
	/// (��ǥ���� �̵����� �ʴ� Renderer���� ���� camera��ŭ�� ������ �̵��Ѵ�)
	/// </summary>
	FVector CameraPos = FVector::Zero;
};

