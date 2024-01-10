//
// Created by 吴启睿 on 2023/10/11.
//

#ifndef INC_90TANKSWAR_PLAYERTANK_H
#define INC_90TANKSWAR_PLAYERTANK_H

#include "movableObject.h"
#include "bullet.h"
#include <QPointF>

class PlayerTank: public MovableObject {
    /// 玩家坦克类 awds移动 j开火 （玩家2 1532移动 0开火）
    /// 子弹发射后有1秒冷却
public:
    explicit PlayerTank(char id_ = 'p');

    void Start();
    void Update() override;

    void Fire(Bullet* bullet);

    int blood = 3;   // 玩家坦克有3条命
    int cooldown = GameDefine::FiringInterval;  // 子弹发射冷却时间

private:
    //  记录上一帧的位置，当越过边界或撞墙时，会将位置重置为上一帧的位置。
    QPointF prevFramePos = QPointF(GameDefine::StartX, GameDefine::StartY);


};


#endif //INC_90TANKSWAR_PLAYERTANK_H
