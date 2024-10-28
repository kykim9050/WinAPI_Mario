#pragma once


// ���� :

class Color8Bit;

class UInGameValue
{
public:


	// ������ŭ ������ ������ ������ ������
	static const int ResultMainWindowXScale;
	static const int ResultMainWindowYScale;


	/// �⺻ ������ ������
	static const int MainWindowXScale;
	static const int MainWindowYScale;

	/// ������ ũ�� ����
	static const int WindowSizeMulValue;

	/// Mario_Rignt.png
	/// �� ��
	static const int MarioRightImageXValue;
	/// �� ��
	static const int MarioRightImageYValue;

	/// Mario_Left.png
	/// �� ��
	static const int MarioLeftImageXValue;
	/// �� ��
	static const int MarioLeftImageYValue;


	static const int UICoinImageXValue;
	static const int UICoinImageYValue;

	// TitleCoin.png
	// �� �� 
	static const int TitleCoinImgX;
	// �� ��
	static const int TitleCoinImgY;

	/// <summary>
	/// ������������ ������ �ʱ� ��ġ
	/// </summary>
	static const int MarioInitXPos;
	static const int MarioInitYPos;

	/// <summary>
	/// ������������ CollisionMap���� ��, �ٴ� ��
	/// </summary>
	static const Color8Bit CollisionColor;

	/// <summary>
	/// CollisionMap���� �浹�� ������ ������ (Actor Pos ����)
	/// </summary>
	static const int ColOffSetX;
	static const int ColOffSetY;

	/// <summary>
	/// UI�̹��� Xũ��, Yũ�� ��
	/// </summary>
	static const int UIXScaleValue;
	static const int UIYScaleValue;

	/// <summary>
	/// Goolba.png ��, �� ��
	/// </summary>
	static const int GoombaImageXValue;
	static const int GoombaImageYValue;

	/// <summary>
	/// Player �� collision scale��
	/// </summary>
	static const int PlayerCollisionScaleX;
	static const int PlayerCollisionScaleY;

	/// <summary>
	/// Goomba �� body Collosion scale ��
	/// </summary>
	static const int GoombaBodyCollisionScaleX;
	static const int GoombaBodyCollisionScaleY;

	/// <summary>
	/// KoopaTroopa_Right.png �� ��, �� ��
	/// </summary>
	static const int KoopaTroopaImageXValue;
	static const int KoopaTroopaImageYValue;

	/// <summary>
	/// KoopaTroopa �� body Collosion scale ��
	/// </summary>
	static const int KoopaTroopaBodyCollisionScaleX;
	static const int KoopaTroopaBodyCollisionScaleY;

	// PiranhaPlant.png �� ��, �� ��
	static const int PiranhaPlantImageXValue;
	static const int PiranhaPlantImageYValue;

	/// <summary>
	/// PiranhaPlant �� Body Collision Scale ��
	/// </summary>
	static const int PiranhaPlantBodyCollisionScaleX;
	static const int PiranhaPlantBodyCollisionScaleY;

	/// <summary>
	/// BrickBlock.png �� ��, �� ��
	/// </summary>
	static const int BrickBlockImageXValue;
	static const int BrickBlockImageYValue;

	/// <summary>
	/// CoinBlock.png �� ��, �� ��
	/// </summary>
	static const int CoinBlockImageXValue;
	static const int CoinBlockImageYValue;

	/// <summary>
	/// Block �� Body Collision Scale ��
	/// </summary>
	static const int BlockCollisionScaleX;
	static const int BlockCollisionScaleY;

	/// <summary>
	/// Coin.png �� ��, �� ��
	/// </summary>
	static const int CoinImageXValue;
	static const int CoinImageYValue;

	/// <summary>
	/// Items.png �� ��, �� ��
	/// </summary>
	static const int ItemsImageXValue;
	static const int ItemsImageYValue;

	/// <summary>
	/// Mushroom�� Body Collision Scale ��
	/// </summary>
	static const int MushroomCollisionScaleX;
	static const int MushroomCollisionScaleY;


	/// <summary>
	/// DebrisBlock.png �� ��, �� ��
	/// </summary>
	static const int DebrisBlockImageXValue;
	static const int DebrisBlockImageYValue;

	/// <summary>
	/// FireFlower�� Body Collision Scale ��
	/// </summary>
	static const int FireFlowerCollisionScaleX;
	static const int FireFlowerCollisionScaleY;

	/// <summary>
	/// ChangingFireMario �� ��, �� ��
	/// </summary>
	static const int ChangingFireMarioImageXValue;
	static const int ChangingFireMarioImageYValue;

	/// <summary>
	/// FireMario �� ��, �� ��
	/// </summary>
	static const int FireMarioImageXValue;
	static const int FireMarioImageYValue;

	/// <summary>
	/// FireBall.png �� ��, �� ��
	/// </summary>
	static const int FireBallImageXValue;
	static const int FireBallImageYValue;

	/// <summary>
	/// EndFlag �� ��ġ��ǥ��
	/// </summary>
	static const int EndFlagXPos;
	static const int EndFlagYPos;

	/// <summary>
	/// EndFlag�� collision Scale ��
	/// </summary>
	static const int EndFlagCollisionXScale;
	static const int EndFlagCollisionYScale;

	/// <summary>
	/// EndPointCastle�� ��ġ ��ǥ��
	/// </summary>
	static const int EndPointCastleXPos;
	static const int EndPointCastleYPos;

	/// <summary>
	/// Stage ������ ������ Collision�� Scale ��
	/// </summary>
	static const int CastleGateCollisionXScale;
	static const int CastleGateCollisionYScale;

	/// <summary>
	/// Numbers.png�� ��, �� ��
	/// </summary>
	static const int NumberImageXValue;
	static const int NumberImageYValue;

	/// <summary>
	/// UI�� TimeRenderer �� size
	/// </summary>
	static const int TimeRendererSize;

	/// <summary>
	/// UI�� ScoreRenderer �� size
	/// </summary>
	static const int ScoreRendererSize;

	/// <summary>
	/// UI�� CoinCountRenderer �� size
	/// </summary>
	static const int CoinCountRendererSize;

	/// <summary>
	/// UI�� StageInfoRenderer �� size
	/// </summary>
	static const int StageInfoRendererSize;
	
	/// <summary>
	/// UI â���� ��µǴ� ������ ���� ��ġ
	/// UI Actor�� ��ǥ�� �������� ������� ��ġ�� ���� ��
	/// </summary>
	static const int UITtimeRendInitXPos;
	static const int UIScoreRendInitXPos;
	static const int UIRendInitYPos;
	static const int UISpacingBetRends;
	static const int UIStageInfoRendInitXPos;

protected:

private:
	UInGameValue();
	~UInGameValue();
};

