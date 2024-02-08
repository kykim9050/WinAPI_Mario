#pragma once
#include <Windows.h>
#include <map>
#include <EngineBase\EngineDebug.h>


// 설명 :
class UEngineInput
{
	friend class InputInitCreator;

private:
	class EngineKey
	{
		friend UEngineInput;

	public:
		bool Down = false; 
		bool Press = false;
		bool Up = false;
		bool Free = true;

		float PressTime = 0.0f;

		int Key = -1; 

		void KeyCheck();

		EngineKey()
		{

		}

		EngineKey(int _Key)
			: Key(_Key)
		{

		}
	};

public:
	// constrcuter destructer
	UEngineInput();
	~UEngineInput();

	// delete Function
	UEngineInput(const UEngineInput& _Other) = delete;
	UEngineInput(UEngineInput&& _Other) noexcept = delete;
	UEngineInput& operator=(const UEngineInput& _Other) = delete;
	UEngineInput& operator=(UEngineInput&& _Other) noexcept = delete;

	static bool IsDown(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Down;
	}

	static bool IsPress(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Press;
	}

	static bool IsUp(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Up;
	}

	static bool IsFree(int _Key)
	{
		if (false == AllKeys.contains(_Key))
		{
			MsgBoxAssert("입력설정이 존재하지 않는 키 입니다");
		}

		return AllKeys[_Key].Free;
	}

	static bool IsAnykeyDown()
	{
		return AnykeyDown;
	}

	static bool IsAnykeyPress()
	{
		return AnykeyPress;
	}

	static bool IsAnykeyUp()
	{
		return AnykeyUp;
	}

	static bool IsAnykeyFree()
	{
		return AnykeyFree;
	}

	static void KeyCheckTick(float _DeltaTime);

protected:
	static std::map<int, EngineKey> AllKeys;

	static bool AnykeyDown;
	static bool AnykeyPress;
	static bool AnykeyUp;
	static bool AnykeyFree;

	int Value;

private:
	static void InputInit();
};

