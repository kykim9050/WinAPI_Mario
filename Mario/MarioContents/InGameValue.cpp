#include "InGameValue.h"
#include <EngineBase/EngineMath.h>

const int UInGameValue::WindowSizeMulValue = 3;
const int UInGameValue::MainWindowXScale = 256;
const int UInGameValue::MainWindowYScale = 240;

const int UInGameValue::ResultMainWindowXScale = UInGameValue::MainWindowXScale * UInGameValue::WindowSizeMulValue;
const int UInGameValue::ResultMainWindowYScale = UInGameValue::MainWindowYScale * UInGameValue::WindowSizeMulValue;


const int UInGameValue::MarioRightImageXValue = 5;
const int UInGameValue::MarioRightImageYValue = 8;

const int UInGameValue::MarioLeftImageXValue = 5;
const int UInGameValue::MarioLeftImageYValue = 8;

const int UInGameValue::TitleCoinImgX = 6;
const int UInGameValue::TitleCoinImgY = 1;
const int UInGameValue::UICoinImageXValue = 3;
const int UInGameValue::UICoinImageYValue = 1;


const int UInGameValue::MarioInitXPos = 140;
const int UInGameValue::MarioInitYPos = 400;

const Color8Bit UInGameValue::CollisionColor = Color8Bit(0, 0, 255, 0);

const int UInGameValue::ColOffSetX = 20;
const int UInGameValue::ColOffSetY = 10;

const int UInGameValue::UIXScaleValue = 256;
const int UInGameValue::UIYScaleValue = 32;

const int UInGameValue::GoombaImageXValue = 3;
const int UInGameValue::GoombaImageYValue = 1;

const int UInGameValue::PlayerCollisionScaleX = 32;
const int UInGameValue::PlayerCollisionScaleY = 40;

const FVector UInGameValue::BigMarioColScale = FVector(32, 72);

const int UInGameValue::GoombaBodyCollisionScaleX = 32;
const int UInGameValue::GoombaBodyCollisionScaleY = 32;

const int UInGameValue::KoopaTroopaImageXValue = 5;
const int UInGameValue::KoopaTroopaImageYValue = 2;

const int UInGameValue::KoopaTroopaBodyCollisionScaleX = 32;
const int UInGameValue::KoopaTroopaBodyCollisionScaleY = 32;

const int UInGameValue::PiranhaPlantImageXValue = 2;
const int UInGameValue::PiranhaPlantImageYValue = 1;

const int UInGameValue::PiranhaPlantBodyCollisionScaleX = 32;
const int UInGameValue::PiranhaPlantBodyCollisionScaleY = 64;

const int UInGameValue::BrickBlockImageXValue = 5;
const int UInGameValue::BrickBlockImageYValue = 1;

const int UInGameValue::CoinBlockImageXValue = 5;
const int UInGameValue::CoinBlockImageYValue = 1;

const int UInGameValue::BlockCollisionScaleX = 16 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::BlockCollisionScaleY = 16 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::CoinImageXValue = 4;
const int UInGameValue::CoinImageYValue = 1;

const int UInGameValue::ItemsImageXValue = 5;
const int UInGameValue::ItemsImageYValue = 2;

const int UInGameValue::MushroomCollisionScaleX = 32;
const int UInGameValue::MushroomCollisionScaleY = 48;

const int UInGameValue::DebrisBlockImageXValue = 5;
const int UInGameValue::DebrisBlockImageYValue = 3;

const int UInGameValue::FireFlowerCollisionScaleX = 32;
const int UInGameValue::FireFlowerCollisionScaleY = 48;

const int UInGameValue::ChangingFireMarioImageXValue = 5;
const int UInGameValue::ChangingFireMarioImageYValue = 2;

const int UInGameValue::FireMarioImageXValue = 5;
const int UInGameValue::FireMarioImageYValue = 9;

const int UInGameValue::FireBallImageXValue = 5;
const int UInGameValue::FireBallImageYValue = 2;

const int UInGameValue::EndFlagXPos = 3176 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::EndFlagYPos = 124 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::EndFlagCollisionXScale = 2 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::EndFlagCollisionYScale = 400 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::EndPointCastleXPos = 3274 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::EndPointCastleYPos = 168 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::CastleGateCollisionXScale = 4 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::CastleGateCollisionYScale = 80 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::NumberImageXValue = 10;
const int UInGameValue::NumberImageYValue = 1;

const int UInGameValue::TimeRendererSize = 3;
const int UInGameValue::ScoreRendererSize = 6;
const int UInGameValue::CoinCountRendererSize = 2;
const int UInGameValue::StageInfoRendererSize = 2;
const int UInGameValue::LifeRendererSize = 1;

const int UInGameValue::UITtimeRendInitXPos = 624;
const int UInGameValue::UIScoreRendInitXPos = 72;
const int UInGameValue::UIRendInitYPos = 72;
const int UInGameValue::UISpacingBetRends = 24;
const int UInGameValue::UIStageInfoRendInitXPos = 459;
const int UInGameValue::UIStageInfoCRendInitXPos = 408;
const int UInGameValue::UIStageInfoCRendInitYPos = 240;
const int UInGameValue::LifeRendInitXPos = 144;
const int UInGameValue::LifeRendInitYPos = 112;
const int UInGameValue::UICoinRendInitXPos = 76;


const int UInGameValue::KoopaImgXValue = 4;
const int UInGameValue::KoopaImgYValue = 1;

const int UInGameValue::KoopaFireImgXValue = 2;
const int UInGameValue::KoopaFireImgYValue = 1;

const int UInGameValue::KoopaBodyCollisionScaleX = 32 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::KoopaBodyCollisionScaleY = 32 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::BridgeBlockAmount = 13;

const int UInGameValue::BridgeStartXPos = 2056 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::BridgeStartYPos = 168 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::BTBDistance = 16 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::KoopaMoveDeadline_F = 300;
const int UInGameValue::KoopaMoveDeadline_R = 100;

const int UInGameValue::KoopaBulletXColScale = 64;
const int UInGameValue::KoopaBulletYColScale = 16;

const int UInGameValue::MovingBoardDeadline_F = 300;
const int UInGameValue::MovingBoardDeadline_R = 0;

const int UInGameValue::MovingBoardInitXPos = 2224 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::MovingBoardInitYPos = 101 * UInGameValue::WindowSizeMulValue;

const int UInGameValue::FootCollisionScaleY = 4;

const int UInGameValue::CastleItemsImgXValue = 5;
const int UInGameValue::CastleItemsImgYValue = 3;

const int UInGameValue::CastleEndFlagXScale = 16 * UInGameValue::WindowSizeMulValue;
const int UInGameValue::CastleEndFlagYScale = 16 * UInGameValue::WindowSizeMulValue;

const FVector UInGameValue::PrincessInitPos = FVector(2440 * UInGameValue::WindowSizeMulValue, 197 * UInGameValue::WindowSizeMulValue );

const FVector UInGameValue::KoopaInitPos = FVector( 2200 * UInGameValue::WindowSizeMulValue, 150 * UInGameValue::WindowSizeMulValue );

const FVector UInGameValue::BossRoomStartLineInitPos = FVector( 2130 * UInGameValue::WindowSizeMulValue, 130 * UInGameValue::WindowSizeMulValue );

const int UInGameValue::MsgHideImgInitYpos = 384;

const int UInGameValue::MessageHInterval = 64;

const int UInGameValue::FireBallDia = 8 * UInGameValue::WindowSizeMulValue;