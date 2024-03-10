#pragma once
#include <EngineBase/EngineMath.h>

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


	static const int UICoinImageXValue;
	static const int UICoinImageYValue;

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
	/// KoopaTroopa_Right.png 의 열, 행 수
	/// </summary>
	static const int KoopaTroopaImageXValue;
	static const int KoopaTroopaImageYValue;

	/// <summary>
	/// KoopaTroopa 의 body Collosion scale 값
	/// </summary>
	static const int KoopaTroopaBodyCollisionScaleX;
	static const int KoopaTroopaBodyCollisionScaleY;

	// PiranhaPlant.png 의 열, 행 수
	static const int PiranhaPlantImageXValue;
	static const int PiranhaPlantImageYValue;

	/// <summary>
	/// PiranhaPlant 의 Body Collision Scale 값
	/// </summary>
	static const int PiranhaPlantBodyCollisionScaleX;
	static const int PiranhaPlantBodyCollisionScaleY;

	/// <summary>
	/// BrickBlock.png 의 열, 행 수
	/// </summary>
	static const int BrickBlockImageXValue;
	static const int BrickBlockImageYValue;

	/// <summary>
	/// CoinBlock.png 의 열, 행 수
	/// </summary>
	static const int CoinBlockImageXValue;
	static const int CoinBlockImageYValue;

	/// <summary>
	/// Block 의 Body Collision Scale 값
	/// </summary>
	static const int BlockCollisionScaleX;
	static const int BlockCollisionScaleY;

	/// <summary>
	/// Coin.png 의 열, 행 수
	/// </summary>
	static const int CoinImageXValue;
	static const int CoinImageYValue;

	/// <summary>
	/// Items.png 의 열, 행 수
	/// </summary>
	static const int ItemsImageXValue;
	static const int ItemsImageYValue;

	/// <summary>
	/// Mushroom의 Body Collision Scale 값
	/// </summary>
	static const int MushroomCollisionScaleX;
	static const int MushroomCollisionScaleY;


	/// <summary>
	/// DebrisBlock.png 의 열, 행 수
	/// </summary>
	static const int DebrisBlockImageXValue;
	static const int DebrisBlockImageYValue;

	/// <summary>
	/// FireFlower의 Body Collision Scale 값
	/// </summary>
	static const int FireFlowerCollisionScaleX;
	static const int FireFlowerCollisionScaleY;

	/// <summary>
	/// ChangingFireMario 의 열, 행 수
	/// </summary>
	static const int ChangingFireMarioImageXValue;
	static const int ChangingFireMarioImageYValue;

	/// <summary>
	/// FireMario 의 열, 행 수
	/// </summary>
	static const int FireMarioImageXValue;
	static const int FireMarioImageYValue;

	/// <summary>
	/// FireBall.png 의 열, 행 수
	/// </summary>
	static const int FireBallImageXValue;
	static const int FireBallImageYValue;

	/// <summary>
	/// EndFlag 의 위치좌표값
	/// </summary>
	static const int EndFlagXPos;
	static const int EndFlagYPos;

	/// <summary>
	/// EndFlag의 collision Scale 값
	/// </summary>
	static const int EndFlagCollisionXScale;
	static const int EndFlagCollisionYScale;

	/// <summary>
	/// EndPointCastle의 위치 좌표값
	/// </summary>
	static const int EndPointCastleXPos;
	static const int EndPointCastleYPos;

	/// <summary>
	/// Stage 마지막 성문의 Collision의 Scale 값
	/// </summary>
	static const int CastleGateCollisionXScale;
	static const int CastleGateCollisionYScale;

	/// <summary>
	/// Numbers.png의 열, 행 수
	/// </summary>
	static const int NumberImageXValue;
	static const int NumberImageYValue;

	/// <summary>
	/// UI의 TimeRenderer 의 size
	/// </summary>
	static const int TimeRendererSize;

	/// <summary>
	/// UI의 ScoreRenderer 의 size
	/// </summary>
	static const int ScoreRendererSize;

	/// <summary>
	/// UI의 CoinCountRenderer 의 size
	/// </summary>
	static const int CoinCountRendererSize;

	/// <summary>
	/// UI의 StageInfoRenderer 의 size
	/// </summary>
	static const int StageInfoRendererSize;
	
	/// <summary>
	/// UI 창에서 출력되는 정보들 관련 수치
	/// UI Actor의 좌표를 원점으로 상대적인 위치에 대한 것
	/// </summary>
	static const int UITtimeRendInitXPos;
	static const int UIScoreRendInitXPos;
	static const int UIRendInitYPos;
	static const int UISpacingBetRends;
	static const int UIStageInfoRendInitXPos;
	static const int UIStageInfoCRendInitXPos;
	static const int UIStageInfoCRendInitYPos;

	/// <summary>
	/// Koopa.png 의 열, 행 수
	/// </summary>
	static const int KoopaImgXValue;
	static const int KoopaImgYValue;

	/// <summary>
	/// KoopaFire.png 의 열, 행 수
	/// </summary>
	static const int KoopaFireImgXValue;
	static const int KoopaFireImgYValue;

	/// <summary>
	/// Koopa의 BodyCollision Scale 값
	/// </summary>
	static const int KoopaBodyCollisionScaleX;
	static const int KoopaBodyCollisionScaleY;

	/// <summary>
	/// 1-4 castle의 bridgeblock의 필요 갯수
	/// </summary>
	static const int BridgeBlockAmount;

	/// <summary>
	/// 1-4 castle의 bridge의 초기 위치
	/// </summary>
	static const int BridgeStartXPos;
	static const int BridgeStartYPos;
	// 1-4 castle의 bridge 사이의 간격
	static const int BTBDistance;

	/// <summary>
	/// 1-4 Stage에서 Koopa의 X축 기준 앞, 뒤 이동 제한 오프셋
	/// </summary>
	static const int KoopaMoveDeadline_F;
	static const int KoopaMoveDeadline_R;

	/// <summary>
	/// Koopa가 발사하는 Bullet의 Collsion Scale
	/// </summary>
	static const int KoopaBulletXColScale;
	static const int KoopaBulletYColScale;

	/// <summary>
	/// Stage1-4 보스방 Moving Board의 X축 기준 앞, 뒤 이동 제한 오프셋
	/// </summary>
	static const int MovingBoardDeadline_F;
	static const int MovingBoardDeadline_R;

	/// <summary>
	/// Stage1-4 보스방 Moving Board의 초기 위치 좌표
	/// </summary>
	static const int MovingBoardInitXPos;
	static const int MovingBoardInitYPos;

	/// <summary>
	/// Player나 Monster의 FootCollision의 y Scale 값
	/// </summary>
	static const int FootCollisionScaleY;

	/// <summary>
	/// CastleItems.png 의 열 , 행 수
	/// </summary>
	static const int CastleItemsImgXValue;
	static const int CastleItemsImgYValue;

	/// <summary>
	/// CastleEndFlag 의 Scale 값
	/// </summary>
	static const int CastleEndFlagXScale;
	static const int CastleEndFlagYScale;

	/// <summary>
	/// 피치공주의 초기 위치 값
	/// </summary>
	static const FVector PrincessInitPos;

	/// <summary>
	/// Koopa의 초기 위치 값
	/// </summary>
	static const FVector KoopaInitPos;

	/// <summary>
	/// Boss 방에서 카메라 이동 정지를 위한 기점이 되는 Line의 위치 값
	/// </summary>
	static const FVector BossRoomStartLineInitPos;

protected:

private:
	UInGameValue();
	~UInGameValue();
};

