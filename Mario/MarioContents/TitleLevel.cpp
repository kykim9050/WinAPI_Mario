#include "TitleLevel.h"
#include <EngineCore\EngineCore.h>
#include "TitleBackGround.h"


UTitleLevel::UTitleLevel()
{
}

UTitleLevel::~UTitleLevel()
{
}

void UTitleLevel::BeginPlay()
{
	ULevel::BeginPlay();

	UTitleBackGround* Background = SpawnActor< UTitleBackGround>();

}

void UTitleLevel::Tick(float _DeltaTime)
{
	ULevel::Tick(_DeltaTime);
}