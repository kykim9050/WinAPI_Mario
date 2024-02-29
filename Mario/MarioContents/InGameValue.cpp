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

const int UInGameValue::MarioInitXPos = 140;
const int UInGameValue::MarioInitYPos = 400;

const Color8Bit UInGameValue::CollisionColor = Color8Bit(0, 0, 255, 0);

const int UInGameValue::ColOffSetX = 20;
const int UInGameValue::ColOffSetY = 40;

const int UInGameValue::UIXScaleValue = 256;
const int UInGameValue::UIYScaleValue = 32;

const int UInGameValue::GoombaImageXValue = 3;
const int UInGameValue::GoombaImageYValue = 1;

const int UInGameValue::PlayerCollisionScaleX = 32;
const int UInGameValue::PlayerCollisionScaleY = 32;

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