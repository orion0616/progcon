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

//------------------------------------------------------------------------------
/// Answer クラスのコンストラクタです。
///
/// @note ここにインスタンス生成時の処理を書くことができますが、何も書かなくても構いません。
Answer::Answer()
{
}

//------------------------------------------------------------------------------
/// Answer クラスのデストラクタです。
///
/// @note ここにインスタンス破棄時の処理を書くことができますが、何も書かなくても構いません。
Answer::~Answer()
{
}

//------------------------------------------------------------------------------
/// 各ステージ開始時に呼び出されます。
///
/// @note ここで、各ステージに対して初期処理を行うことができます。
///
/// @param[in] aStage 現在のステージ。
void Answer::init(const Stage& aStage)
{
}

//------------------------------------------------------------------------------
/// 各ターンでの行動を返します。
///
/// @param[in] aStage 現在ステージの情報。
///
/// @return これから行う行動を表す Action クラス。
Action Answer::getNextAction(const Stage& aStage)
{
    // レーザーが発射できるときは、レーザーを発射します。
    // レーザーが発射できないときは、移動します。
    if(aStage.ship().canShoot()) {
        // 発射目標にする小惑星を決定します。
        Vector2 targetShootPos;
        for(int i = aStage.asteroidCount() - 1; i >= 0; --i) {
            if(aStage.asteroid(i).exists()) {
                targetShootPos = aStage.asteroid(i).pos();
                break;
            }
        }
        return Action::Shoot(targetShootPos);
    } else {
        // 移動目標にする小惑星を決定します。
        Vector2 targetMovePos;
        for(int i = 0; i < aStage.asteroidCount(); ++i) {
            if(aStage.asteroid(i).exists()) {
                targetMovePos = aStage.asteroid(i).pos();
                break;
            }
        }
        return Action::Move(targetMovePos);
    }
}

//------------------------------------------------------------------------------
/// 各ステージ終了時に呼び出されます。
///
/// @param[in] aStage 現在ステージの情報。
///
/// @note ここにステージ終了時の処理を書くことができますが、何も書かなくても構いません。
void Answer::finalize(const Stage& aStage)
{
}

} // namespace
// EOF
