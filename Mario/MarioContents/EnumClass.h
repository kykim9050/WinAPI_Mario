#pragma once

/// <summary>
/// 타이틀 랜더링 순서
/// </summary>
enum class ETitleRenderOrder
{
	BackGroundMap,
	Coin,
};

/// <summary>
/// 엔딩 랜더링 순서
/// </summary>
enum class EEndingRenderOrder
{
	BackGroundMap,
	UI,
	Message,
	MessageHide,
};

/// <summary>
/// 스테이지 랜더러 순서
/// </summary>
enum class EStageRenderOrder
{
	CollisionMap,
	BackGroundMap,
	BackGrundSubStructure,
	BackGrundStructure,
	Item,
	Block,
	AttackableTrap,
	Score,
	Monster,
	Mario,
	ObjectHideStructure,
	Bullet,
	UI,
	UIComponent,
	IntroUI,
	IntroUIComponent,
	Manual,
};

/// <summary>
/// Actor의 상태
/// </summary>
enum class EActorState
{
	None,
	FirstInit,
	Idle,
	Move,
	FreeMove,
	CameraMove,
	ReverseMove,
	Jump,
	CollisionJump,
	Rotating,
	FallDown,
	Dead,
	OnTheBlock,
	GetHit,
	GetFirstHit,
	GetSecondHit,
	GetMonsterHit,
	GetBlockHit,
	Appear,
	Fixed,
	Debris,
	Release,
	MarioGrowUp,
	FireMario,
	Wait,
	ReachingEndFlag,
	ReachStageEnd,
	BossStageClear,
	Fire,
	IdleFireThrow,
	MoveFireThrow,
	ReverseMoveFireThrow,
	JumpFireThrow,
	Speak,
	Explosion,
};

enum class EActorDir
{
	None,
	Left,
	Right,
};

/// <summary>
/// 액터의 종류
/// </summary>
enum class EActorType
{
	None,
	Map,
	UI,
	Intro,
	Player,
	Monster,
	Structure,
	Block,
	Item,
	Bullet,
	AttackableTrap,
	ScoreImg,
	Manual,
};

enum class EMarioType
{
	None,
	Small,
	Big,
	Fire,
};

enum class ECollisionOrder
{
	PlayerBullet,
	MonsterBullet,
	Monster,
	MonsterFootCollision,
	Player,
	PlayerFootCollision,
	AttackableMonster,
	BlockSide,
	BlockBot,
	BlockTop,
	Item,
	Mushroom,
	FireFlower,
	Invincible,
	EndFlagLine,
	CastleGate,
	CastleEndFlag,
	SignalCol,
	AttackableTrap,
};

enum class ECollisionState
{
	None,
	Hit,
	GetHit,
	OneHit,
	TwoHit,
	GetMonsterHit,
	BlockBotHit,
	BlockSideHit,
	Invincible,
};

enum class EItemType
{
	None,
	Coin,
	Item,
};