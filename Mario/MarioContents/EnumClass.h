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
	Mario,
	Monster,
};

/// <summary>
/// �÷��̾��� ����
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