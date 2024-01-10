//
// Created by WQR on 2023/10/13.
//

#ifndef INC_90TANKSWAR_BULLET_H
#define INC_90TANKSWAR_BULLET_H

#include "movableObject.h"

class Bullet: public MovableObject{
    /// 子弹类：
    ///  可穿过森林、河流，可击毁非己方坦克、墙，同时自己也销毁。
public:
    Bullet();
    char belong;  // 子弹所属方，其值等于发射方的id

    void Update() override;
};


#endif //INC_90TANKSWAR_BULLET_H
