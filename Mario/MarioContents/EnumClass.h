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
	Item,
	Block,
	Monster,
	Mario,
	UI,
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
	Player,
	Monster,
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