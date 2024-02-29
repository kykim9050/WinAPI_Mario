#include "BlockCoin.h"

ABlockCoin::ABlockCoin()
{
}

ABlockCoin::~ABlockCoin()
{
}


void ABlockCoin::BeginPlay()
{
	AItemUnit::BeginPlay();

	Renderer = CreateImageRenderer(static_cast<int>(EStageRenderOrder::Item));
	Renderer->SetImage("Coin.png");

	FVector ItemScale = Renderer->GetImage()->GetScale();

	Renderer->SetTransform({ {0,0}, {ItemScale.iX() / UInGameValue::CoinImageXValue, ItemScale.iY() / UInGameValue::CoinImageYValue} });
	Renderer->CreateAnimation("Rotating_Coin", "Coin.png", 0, 3, 0.05f, true);
	Renderer->ChangeAnimation("Rotating_Coin");

	StateChange(EActorState::Idle);
}

void ABlockCoin::Tick(float _DeltaTime)
{
	AItemUnit::Tick(_DeltaTime);
}


void ABlockCoin::Appear(float _DeltaTime)
{
	AItemUnit::Appear(_DeltaTime);

	// 동전의 경우
	CoinRenderingTime -= _DeltaTime;

	if (false == RenderingEnd && 0.0f >= CoinRenderingTime)
	{
		RenderingEnd = true;
		GravityVelocityVector = FVector::Zero;
		JumpVelocityVector = FVector::Zero;
		StateChange(EActorState::Release);
	}

	GravityVelocityVector += GravityAccVector * _DeltaTime;
	CalTotalVelocityVector(_DeltaTime);
	AddActorLocation(TotalVelocityVector * _DeltaTime);
}


void ABlockCoin::IdleStart()
{
	AItemUnit::IdleStart();

	Renderer->ActiveOff();
}

void ABlockCoin::AppearStart()
{
	AItemUnit::AppearStart();

	JumpVelocityVector = FVector::Up * 600.0f;
	Renderer->ActiveOn();
}

void ABlockCoin::ReleaseStart()
{
	AItemUnit::ReleaseStart();
	// 랜더링만 Destroy
	// 액터 자체를 Destory하면 BlockUnit에서 사용할 수가 없음
	Renderer->Destroy();
}