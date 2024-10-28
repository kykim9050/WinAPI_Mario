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
	MessageHideRenderer->SetTransform({ { UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), 384},{MessageHideScale}});
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
			MessageHideRenderer->SetTransform({ {UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), 384 + 32},{MessageHideScale.iX(), MessageHideScale.iY() - (2 * 32)} });
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
				MessageHideRenderer->SetTransform({ {UContentsFunction::CollisionMapSize().iX() - MessageHideScale.ihX(), 384 + 32 * MsgStep},{MessageHideScale.iX(), MessageHideScale.iY() - (2 * 32 * MsgStep)} });
				break;
			}
			break;
		}
		case 5:
		{
			// ���������� �Ѿ �� �ְ� Level���� Ű Ȱ��ȭ ���ִ� ��� ����
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
		MsgBoxAssert("Princess�� BodyCollision�� null�Դϴ�.");
		return;
	}

	if (true == BodyCollision->CollisionCheck(ECollisionOrder::Player, Result))
	{
		BodyCollision->ActiveOff();
		GetPlayer()->MeetThePrincess();
		return;
	}
}

