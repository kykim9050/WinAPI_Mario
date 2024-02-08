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

	UImageRenderer* MessageRenderer = CreateImageRenderer(static_cast<int>(EndingRenderOrder::Message));
	
	// UImageRenderer를 5개 만들고 따로따로 이미지 잘라서 저장 출력하게 만들기 (Message에서 자료구조로 각 이미지를 갖고 있도록 하자)
	// 메세지별로 매칭되는 프레임 자료구조도 만들어서 함께 호출할 수 있도록 하기
	MessageRenderer->SetImage("Mario_Ending_BackGround_Message.png");
	FVector ImageScale = MessageRenderer->GetImage()->GetScale();
	MessageRenderer->SetTransform({ {ImageScale.ihX(), ImageScale.ihY()},{ImageScale.iX(),ImageScale.iY() / MessageNum}});


}

void AEndingMessage::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}