#pragma once

/// <summary>
/// Ÿ��Ʋ ������ ����
/// </summary>
enum class TitleRenderOrder
{
	BackGroundMap,
	Coin,
};

/// <summary>
/// ���� ������ ����
/// </summary>
enum class EndingRenderOrder
{
	BackGroundMap,
	UI,
	Message,
	MessageHide,
};

/// <summary>
/// �������� ������ ����
/// </summary>
enum class StageRenderOrder
{
	BackGroundMap,
	Mario,
	Monster,
};

/// <summary>
/// �÷��̾��� ����
/// </summary>
enum class PlayerState
{
	None,
	FreeMove,
	CameraMove,
	Idle,
	Move,
	Jump,
};