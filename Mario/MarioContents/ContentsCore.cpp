#include "ContentsCore.h"
#include "TitleLevel.h"
#include "1_1StageLevel.h"
#include "1_4StageLevel.h"
#include "EndingLevel.h"
#include "TestLevel.h"
#include <EngineBase/EngineDirectory.h>
#include <EngineBase/EngineFile.h>
#include <EngineCore/EngineResourcesManager.h>
#include "InGameValue.h"
#include "PlayerScoreManager.h"



UContentsCore::UContentsCore()
	: UEngineCore()
{
}

UContentsCore::~UContentsCore()
{
}

// 프로그램 시작
void UContentsCore::BeginPlay()
{
	UEngineCore::BeginPlay();


	// 마리오용 윈도우 크기 설정
	MainWindow.SetWindowScale({ UInGameValue::MainWindowXScale * UInGameValue::WindowSizeMulValue, UInGameValue::MainWindowYScale * UInGameValue::WindowSizeMulValue });


	UEngineDirectory ResourcesDir = UEngineDirectory();

	ResourcesDir.MoveToSearchChild("Resources");

	std::list<UEngineFile> ResourcesList = ResourcesDir.AllFile({ ".png" }, true);

	for (UEngineFile& CurFIle : ResourcesList)
	{
		UEngineResourcesManager::GetInst().LoadImg(CurFIle.GetFullPath());
	}

	UEngineResourcesManager::GetInst().CuttingImage("TitleCoin.png", UInGameValue::TitleCoinImgX, UInGameValue::TitleCoinImgY);
	UEngineResourcesManager::GetInst().CuttingImage("Mario_Right.png", UInGameValue::MarioRightImageXValue, UInGameValue::MarioRightImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Mario_Left.png", UInGameValue::MarioLeftImageXValue, UInGameValue::MarioLeftImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Goomba.png", UInGameValue::GoombaImageXValue, UInGameValue::GoombaImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("KoopaTroopa_Left.png", UInGameValue::KoopaTroopaImageXValue, UInGameValue::KoopaTroopaImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("KoopaTroopa_Right.png", UInGameValue::KoopaTroopaImageXValue, UInGameValue::KoopaTroopaImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("PiranhaPlant.png", UInGameValue::PiranhaPlantImageXValue, UInGameValue::PiranhaPlantImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("BrickBlock.png", UInGameValue::BrickBlockImageXValue, UInGameValue::BrickBlockImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("CoinBlock.png", UInGameValue::CoinBlockImageXValue, UInGameValue::CoinBlockImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Coin.png", UInGameValue::CoinImageXValue, UInGameValue::CoinImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Items.png", UInGameValue::ItemsImageXValue, UInGameValue::ItemsImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("DebrisBlock.png", UInGameValue::DebrisBlockImageXValue, UInGameValue::DebrisBlockImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("ChangingFireMario_Left.png", UInGameValue::ChangingFireMarioImageXValue, UInGameValue::ChangingFireMarioImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("ChangingFireMario_Right.png", UInGameValue::ChangingFireMarioImageXValue, UInGameValue::ChangingFireMarioImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("FireMario_Left.png", UInGameValue::FireMarioImageXValue, UInGameValue::FireMarioImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("FireMario_Right.png", UInGameValue::FireMarioImageXValue, UInGameValue::FireMarioImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("FireBall.png", UInGameValue::FireBallImageXValue, UInGameValue::FireBallImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Numbers.png", UInGameValue::NumberImageXValue, UInGameValue::NumberImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("UICoin.png", UInGameValue::UICoinImageXValue, UInGameValue::UICoinImageYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Koopa_Left.png", UInGameValue::KoopaImgXValue, UInGameValue::KoopaImgYValue);
	UEngineResourcesManager::GetInst().CuttingImage("Koopa_Right.png", UInGameValue::KoopaImgXValue, UInGameValue::KoopaImgYValue);
	UEngineResourcesManager::GetInst().CuttingImage("KoopaFire_Left.png", UInGameValue::KoopaFireImgXValue, UInGameValue::KoopaFireImgYValue);
	UEngineResourcesManager::GetInst().CuttingImage("KoopaFire_Right.png", UInGameValue::KoopaFireImgXValue, UInGameValue::KoopaFireImgYValue);


	//CreateLevel<UTitleLevel>("TitleLevel");
	//CreateLevel<UIntroLevel>("IntroLevel");
	//CreateLevel<UEndingLevel>("EndingLevel");
	
	//CreateLevel<U1_1StageLevel>("1-1");
	//ChangeLevel("1-1");

	CreateLevel<UTestLevel>("1-4");
	ChangeLevel("1-4");

	//CreateLevel<U1_4StageLevel>("1-4");
	//ChangeLevel("1-4");

	//CreateLevel<UTitleLevel>("TitleLevel");
	//ChangeLevel("TitleLevel");

}

void UContentsCore::Tick(float _DeltaTime)
{
	UEngineCore::Tick(_DeltaTime);

	DebugModeUpdate(_DeltaTime);

}

void UContentsCore::End()
{
	UEngineCore::End();
}

void UContentsCore::DebugModeUpdate(float _DeltaTime)
{
	if (true == UEngineInput::IsDown(VK_F2))
	{
		GEngine->EngineDebugSwitch();
	}
}