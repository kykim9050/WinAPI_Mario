#include "Princess.h"
#include "PlayerMario.h"
#include "ContentsFunction.h"

bool APrincess::PrintMsg = false;

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

	MessageHideScale = MessageHideRenderer->GetImage()->GetScale();
	MessageHideRenderer->SetTransform({ { UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), UInGameValue::MsgHideImgInitYpos},{MessageHideScale}});
}

void APrincess::Tick(float _DeltaTime)
{
	UStateUnit::Tick(_DeltaTime);

	if (true == IsCanPrintMsg())
	{
		static int MsgStep = 0;
		static float DelayTime = 3.0f;


		switch (MsgStep)
		{
		case 0:
		{
			MessageHideRenderer->SetTransform({ {UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), UInGameValue::MsgHideImgInitYpos + static_cast<int>(UInGameValue::MessageHInterval / 2)},{MessageHideScale.iX(), MessageHideScale.iY() - (UInGameValue::MessageHInterval)} });
			++MsgStep;
			break;
		}
		case 1:
		case 2:
		case 3:
		case 4:
		{
			DelayTime -= _DeltaTime;

			if (0.0f >= DelayTime)
			{
				++MsgStep;
				DelayTime = 1.0f + DelayTime;
				MessageHideRenderer->SetTransform({ {UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), UInGameValue::MsgHideImgInitYpos + static_cast<int>(UInGameValue::MessageHInterval / 2) * MsgStep},{MessageHideScale.iX(), MessageHideScale.iY() - (UInGameValue::MessageHInterval * MsgStep)} });
				break;
			}
			break;
		}
		case 5:
		{
			// 엔딩레벨로 넘어갈 수 있게 Level에게 키 활성화 해주는 기능 구현
			PrintMsg = false;
			break;
		}
		default:
			break;
		}

	}
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

