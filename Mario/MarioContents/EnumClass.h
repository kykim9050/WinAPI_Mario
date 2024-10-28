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
	FreeMove,
	CameraMove,
	Idle,
	Move,
	Jump,
	ReverseMove,
	CollisionJump,
	GetHit,
	GetFirstHit,
	GetSecondHit,
	GetMonsterHit,
	Dead,
	Fixed,
	OnTheBlock,
	Release,
};

enum class EActorDir
{
	None,
	Left,
	Right,
};


enum class ECollisionOrder
{
	PlayerBullet,
	Monster,
	Player,
	AttackableMonster,
	Block,
	CollisionBlock,
	BlockTop,
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
	BlockTopHit,
};