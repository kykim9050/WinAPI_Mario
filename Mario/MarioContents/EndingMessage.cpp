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

	UImageRenderer* MessageRenderer = CreateImageRenderer(static_cast<int>(EEndingRenderOrder::Message));
	MessageHideRenderer = CreateImageRenderer(static_cast<int>(EEndingRenderOrder::MessageHide));

	MessageRenderer->SetImage("Mario_Ending_BackGround_Message.png");
	FVector MessageScale = MessageRenderer->GetImage()->GetScale();
	MessageRenderer->SetTransform({ {MessageScale.ihX(), MessageScale.ihY() + 200},{MessageScale} });

	MessageHideRenderer->SetImage("Mario_Ending_BackGround_Message_Hide.png");
	MessageHideScale = MessageHideRenderer->GetImage()->GetScale();
	MessageHideRenderer->SetTransform({ {MessageHideScale.ihX(), MessageHideScale.ihY() + 200},{MessageHideScale} });

}

void AEndingMessage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);

	MessageOutPutIntervalTime -= _DeltaTime;

	

	if (0 >= MessageOutPutIntervalTime)
	{
		if (1 <= CurMessageNum)
		{
			MessageHideRenderer->SetTransform({ {MessageHideScale.ihX(), MessageHideScale.ihY() + 200 + (64/2* MessageVal)},{MessageHideScale.iX(), MessageHideScale.iY() - (64 * MessageVal++)}});
			--CurMessageNum;
			MessageOutPutIntervalTime = 1.0f;
		}
	}

}