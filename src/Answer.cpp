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

float calcTheta(Asteroid a, Vector2 v) {
    float dist = a.pos().dist(v);
    float r = a.radius();
    float theta = Math::ACos(Math::Sqrt(dist*dist-r*r)/dist);
    return Math::Abs(theta);
}

Action Answer::getNextAction(const Stage& aStage)
{
    // レーザーが発射できるときは、レーザーを発射します。
    // レーザーが発射できないときは、移動します
    Ship ship = aStage.ship();
    Vector2 shipLocation = ship.pos();
    Vector2 nearest = Vector2(100000,100000);
    float epsilon = 0.0001;
    if(ship.canShoot()) {
        // 発射目標にする小惑星を決定します。
        Vector2 targetShootPos;
        for(int i = 0; i < aStage.asteroidCount(); i++) {
            Asteroid a1 = aStage.asteroid(i);
            if(!a1.exists())
                continue;
            float theta1 = calcTheta(a1, shipLocation);
            Vector2 a1loc = a1.pos() - shipLocation;
            for(int j = i+1; j < aStage.asteroidCount(); j++) {
                Asteroid a2 = aStage.asteroid(j);
                if(!a2.exists()) 
                    continue;
                float theta2 = calcTheta(a2, shipLocation);
                Vector2 a2loc = a2.pos() - shipLocation;
                if(a1loc.angle(a2loc) < theta1 + theta2){
                    if(a1loc.rotSign(a2loc) > 0)
                        targetShootPos = a1loc.getRotatedRad(theta1-epsilon)+shipLocation;
                    else
                        targetShootPos = a1loc.getRotatedRad(-theta1+epsilon)+shipLocation;
                    return Action::Shoot(targetShootPos);
                }   
            }
            targetShootPos = a1.pos();
        }
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
