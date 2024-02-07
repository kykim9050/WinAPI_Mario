#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>
#include <string_view>

namespace EngineDebug
{
#define LeakCheck _CrtSetDbgFlag(_CRTDBG_LEAK_CHECK_DF | _CRTDBG_ALLOC_MEM_DF);
#define MsgBoxAssert(Value) \
	std::string ErrorText = std::string(Value); \
	MessageBoxA(nullptr, ErrorText.c_str(), "치명적 에러", MB_OK); assert(false);

	/// <summary>
	/// 출력창에서 _DebugText내용을 확인할 수 있게 해주는 함수
	/// 디버깅용
	/// </summary>
	/// <param name="_DebugText"></param>
	void OutPutDebugText(std::string_view _DebugText);
}

