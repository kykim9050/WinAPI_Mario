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
};

enum class ECollisionState
{
	None,
	Hit,
	GetHit,
	OneHit,
	TwoHit,
	GetMonsterHit,
};