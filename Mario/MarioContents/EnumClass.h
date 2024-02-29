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
	Item,
	Block,
	Monster,
	Mario,
	UI,
};

/// <summary>
/// Actor의 상태
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
	Appear,
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
	Player,
	Monster,
	Block,
	Item,
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
	Item,
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