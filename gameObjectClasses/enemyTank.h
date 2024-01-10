//
// Created by WQR on 2023/10/14.
//

#ifndef INC_90TANKSWAR_ENEMYTANK_H
#define INC_90TANKSWAR_ENEMYTANK_H

#include "movableObject.h"
#include "bullet.h"


class EnemyTank: public MovableObject{
    /// 敌方坦克类：
    /// 撞墙后随机转向，子弹每1秒发射一次。
public:
    EnemyTank();

    void Update() override;

    void Fire(Bullet* bullet);

private:
    QPointF prevFramePos = QPointF(1, 1);

    int cnt = 0;
};


#endif //INC_90TANKSWAR_ENEMYTANK_H
