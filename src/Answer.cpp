//------------------------------------------------------------------------------
/// @file
/// @author   ハル研究所プログラミングコンテスト実行委員会
///
/// @copyright  Copyright (c) 2016 HAL Laboratory, Inc.
/// @attention  このファイルの利用は、同梱のREADMEにある
///             利用条件に従ってください
//------------------------------------------------------------------------------

#include "Answer.hpp"

/// プロコン問題環境を表します。
namespace hpc {
Answer::Answer()
{
}

Answer::~Answer()
{
}

/// @note ここで、各ステージに対して初期処理を行うことができます。
/// @param[in] aStage 現在のステージ。
void Answer::init(const Stage& aStage)
{
}

/// 各ターンでの行動を返します。
/// @param[in] aStage 現在ステージの情報。
/// @return これから行う行動を表す Action クラス。
Action Answer::getNextAction(const Stage& aStage)
{
    // レーザーが発射できるときは、レーザーを発射します。
    // レーザーが発射できないときは、移動します。
    Ship ship = aStage.ship();
    Vector2 shipLocation = ship.pos();
    Vector2 farest = Vector2(0,0);
    Vector2 nearest = Vector2(100000,100000);
    if(ship.canShoot()) {
        float farLength = farest.dist(shipLocation);
        // 発射目標にする小惑星を決定します。
        Vector2 targetShootPos;
        for(int i = aStage.asteroidCount() - 1; i >= 0; --i) {
            if(aStage.asteroid(i).exists()) {
                if(farLength < aStage.asteroid(i).pos().dist(shipLocation)){
                    farest = aStage.asteroid(i).pos();
                    farLength = farest.dist(shipLocation);
                }
            }
        }
        targetShootPos = farest;
        return Action::Shoot(targetShootPos);
    } else {
        float nearLength = nearest.dist(shipLocation);
        // 移動目標にする小惑星を決定します。
        Vector2 targetMovePos;
        for(int i = 0; i < aStage.asteroidCount(); ++i) {
            if(aStage.asteroid(i).exists()) {
                if(nearLength > aStage.asteroid(i).pos().dist(shipLocation)){
                    nearest = aStage.asteroid(i).pos();
                    nearLength = nearest.dist(shipLocation);
                }
            }
        }
        targetMovePos = nearest;
        return Action::Move(targetMovePos);
    }
}

/// 各ステージ終了時に呼び出されます。
/// @param[in] aStage 現在ステージの情報。
void Answer::finalize(const Stage& aStage)
{
}
} // namespace
// EOF
