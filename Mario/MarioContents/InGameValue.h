#pragma once


// 설명 :

class Color8Bit;

class UInGameValue
{
public:


	// 배율만큼 곱해진 변현된 윈도우 사이즈
	static const int ResultMainWindowXScale;
	static const int ResultMainWindowYScale;


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

	/// <summary>
	/// UI이미지 X크기, Y크기 값
	/// </summary>
	static const int UIXScaleValue;
	static const int UIYScaleValue;

	/// <summary>
	/// Goolba.png 열, 행 수
	/// </summary>
	static const int GoombaImageXValue;
	static const int GoombaImageYValue;

	/// <summary>
	/// Player 의 collision scale값
	/// </summary>
	static const int PlayerCollisionScaleX;
	static const int PlayerCollisionScaleY;

	/// <summary>
	/// Goomba 의 body Collosion scale 값
	/// </summary>
	static const int GoombaBodyCollisionScaleX;
	static const int GoombaBodyCollisionScaleY;

	/// <summary>
	/// 
	/// </summary>
	static const int KoopaTroopaImageXValue;
	static const int KoopaTroopaImageYValue;

protected:

private:

};

