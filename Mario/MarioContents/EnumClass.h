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
	BackGrundStructure,
	Item,
	Block,
	Monster,
	Mario,
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
	Fire,
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
	Monster,
	Player,
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