//
// Created by My on 2023/10/17.
//

#ifndef INC_90TANKSWAR_BOMB_H
#define INC_90TANKSWAR_BOMB_H

#include "movableObject.h"

class Bomb: public MovableObject{
    /// 爆炸类：
    /// 该游戏对象在子弹被销毁时出现，且出现很短时间后就消失
public:
    Bomb();

    void Update() override;

private:
    int life = 50;  // 爆炸持续时间（ms）
};


#endif //INC_90TANKSWAR_BOMB_H
