//
// Created by WQR on 2023/10/11.
//

#ifndef INC_90TANKSWAR_GAMEOBJECT_H
#define INC_90TANKSWAR_GAMEOBJECT_H


#include "gameDefine.h"


class GameObject : public QGraphicsPixmapItem {

public:
    /// 每类游戏对象均有唯一的id，如下：
    /// 石头  1
    ///  墙  2
    ///  河流 3
    ///  森林 4

    /// 玩家坦克 p （q）
    /// 敌方坦克 e
    /// 子弹   b
    ///  营地  c
    char id = '0';

    QPixmap imgs[4];

    bool isDestroyed = false;

    GameObject();
    bool isOnBound() const;  // 判断是否在界内


};


#endif //INC_90TANKSWAR_GAMEOBJECT_H
