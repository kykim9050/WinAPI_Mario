#pragma once


// 설명 :

class Color8Bit;

class UInGameValue
{
public:

	/// 기본 윈도우 사이즈
	static const int MainWindowXScale;
	static const int MainWindowYScale;

	/// 윈도우 크기 배율
	static const int WindowSizeMulValue;

	/// Mario_Rignt.png
	/// 열 수
	static const int MarioRightImageXValue;
	/// 행 수
	static const int MarioRightImageYValue;

	/// Mario_Left.png
	/// 열 수
	static const int MarioLeftImageXValue;
	/// 행 수
	static const int MarioLeftImageYValue;

	// TitleCoin.png
	// 열 수 
	static const int TitleCoinImgX;
	// 행 수
	static const int TitleCoinImgY;

	/// <summary>
	/// 스테이지에서 마리오 초기 위치
	/// </summary>
	static const int MarioInitXPos;
	static const int MarioInitYPos;

	/// <summary>
	/// 스테이지에서 CollisionMap에서 벽, 바닥 색
	/// </summary>
	static const Color8Bit CollisionColor;

	/// <summary>
	/// CollisionMap에서 충돌할 오프셋 사이즈 (Actor Pos 기준)
	/// </summary>
	static const int ColOffSetX;
	static const int ColOffSetY;


protected:

private:

};

