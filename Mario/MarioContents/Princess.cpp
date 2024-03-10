#include "Princess.h"
#include "PlayerMario.h"

APrincess::APrincess()
{
}

APrincess::~APrincess()
{
}

void APrincess::BeginPlay()
{
	UStateUnit::BeginPlay();

	BodyCollision = CreateCollision(ECollisionOrder::Player);
	BodyCollision->SetTransform({ { 2440 * 3, 197 * 3 }, { UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY } });
	BodyCollision->SetColType(ECollisionType::Rect);

	MessageHideRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::UIComponent));
	MessageHideRenderer->SetImage("Mario_Ending_BackGround_Message_Hide.png");

	FVector MessageHideScale = MessageHideRenderer->GetImage()->GetScale();
	MessageHideRenderer->SetTransform({ { 7680 - MessageHideScale.ihX(), static_cast<int>(720/2)},{MessageHideScale}});
}

void APrincess::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);
}

void APrincess::CollisionCheck()
{
	UStateUnit::CollisionCheck();

	std::vector<UCollision*> Result = std::vector<UCollision*>();

	if (nullptr == BodyCollision)
	{
		MsgBoxAssert("Princess의 BodyCollision이 null입니다.");
		return;
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->ActiveOff();
		GetPlayer()->MeetThePrincess();
		return;
	}
}