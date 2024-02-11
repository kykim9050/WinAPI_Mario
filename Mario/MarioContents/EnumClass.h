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
	Mario,
	Monster,
};

/// <summary>
/// 플레이어의 상태
/// </summary>
enum class EPlayerState
{
	None,
	FreeMove,
	CameraMove,
	Idle,
	Move,
	Jump,
};

enum class EPlayerDir
{
	None,
	Left,
	Right,
};