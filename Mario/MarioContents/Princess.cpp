#include "Princess.h"
#include "PlayerMario.h"
#include "ContentsFunction.h"

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
	BodyCollision->SetTransform({ { UInGameValue::PrincessInitPos.iX(), UInGameValue::PrincessInitPos.iY() }, { UInGameValue::PlayerCollisionScaleX, UInGameValue::PlayerCollisionScaleY } });
	BodyCollision->SetColType(ECollisionType::Rect);

	MessageHideRenderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::BackGrundStructure));
	MessageHideRenderer->SetImage("Mario_Ending_BackGround_Message_Hide.png");

	FVector MessageHideScale = MessageHideRenderer->GetImage()->GetScale();
	MessageHideRenderer->SetTransform({ { UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), UContentsFunction::CollisionMapSize().ihY()},{MessageHideScale}});
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