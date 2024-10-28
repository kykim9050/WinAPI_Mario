#pragma once

/// <summary>
/// Ÿ��Ʋ ������ ����
/// </summary>
enum class ETitleRenderOrder
{
	BackGroundMap,
	Coin,
};

/// <summary>
/// ���� ������ ����
/// </summary>
enum class EEndingRenderOrder
{
	BackGroundMap,
	UI,
	Message,
	MessageHide,
};

/// <summary>
/// �������� ������ ����
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
	Bullet,
	UI,
	UIComponent,
	IntroUI,
	IntroUIComponent,
};

/// <summary>
/// Actor�� ����
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
	Speak,
};

enum class EActorDir
{
	None,
	Left,
	Right,
};

/// <summary>
/// ������ ����
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