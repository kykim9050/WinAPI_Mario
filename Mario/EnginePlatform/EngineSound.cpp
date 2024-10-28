#include "EngineSound.h"
#include <EngineBase\EngineString.h>
#include <EngineBase\EngineDebug.h>

// Debug �϶���
// #pragma comment(lib, "ThirdParty\\FMOD\\inc\\fmodL_vc.lib")
#pragma comment(lib, "fmodL_vc.lib")

// Release �϶��� 
// #pragma comment(lib, "fmod_vc.lib")

std::map<std::string, UEngineSound*> UEngineSound::Resources;

void UEngineSound::ResourcesRelease()
{
	for (std::pair<const std::string, UEngineSound*>& Pair : Resources)
	{
		delete Pair.second;
	}

	Resources.clear();
}

UEngineSound::UEngineSound()
{
}

UEngineSound::~UEngineSound()
{
}


void UEngineSound::Load(std::string_view _Path, std::string_view _Name)
{
	std::string UpperName = UEngineString::ToUpper(_Name);

	if (true == Resources.contains(UpperName))
	{
		MsgBoxAssert("�̹� �ε��� ���ҽ��� �� �ε� �Ϸ��� �߽��ϴ�.");
		return;
	}

	UEngineSound* NewSound = new UEngineSound();
	Resources[_Name.data()] = NewSound;
}