#include "EndingMessage.h"
#include "EnumClass.h"

AEndingMessage::AEndingMessage()
{
}

AEndingMessage::~AEndingMessage()
{
}

void AEndingMessage::BeginPlay()
{
	AActor::BeginPlay();

	UImageRenderer* MessageRenderer = CreateImageRenderer(static_cast<int>(TitleRenderOrder::Coin));
	MessageRenderer->SetImage("Mario_Ending_BackGround_Message.png");
	FVector ImageScale = MessageRenderer->GetImage()->GetScale();
	MessageRenderer->SetTransform({ {ImageScale.ihX(), ImageScale.ihY()},{ImageScale} });

	MessageRenderer->CreateAnimation("Ending_Message", "Mario_Ending_BackGround_Message.png", 0, 4, 1, false);
	MessageRenderer->ChangeAnimation("Ending_Message");
}

void AEndingMessage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}