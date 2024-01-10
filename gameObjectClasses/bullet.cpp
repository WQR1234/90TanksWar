//
// Created by WQR on 2023/10/13.
//

#include "bullet.h"
#include <QDebug>

Bullet::Bullet() {
    id = 'b';

    speed = 12;
    imgs[0].load(":/images/bullet-0.gif");
    imgs[0] = imgs[0].scaled(12, 12);
    imgs[1].load(":/images/bullet-1.gif");
    imgs[1] = imgs[1].scaled(12, 12);
    imgs[2].load(":/images/bullet-2.gif");
    imgs[2] = imgs[2].scaled(12, 12);
    imgs[3].load(":/images/bullet-3.gif");
    imgs[3] = imgs[3].scaled(12, 12);

}

void Bullet::Update() {
    Move();

    // 出界则销毁
    if (!isOnBound()) isDestroyed = true;

    // 碰撞检测
    auto collidedItems= this->collidingItems();  // 拿到所有与其碰撞的游戏对象
    GameObject* obj = nullptr;
    for (auto item:collidedItems) {
        obj = (GameObject*)item;
        switch (obj->id) {
            case '1':  //  撞上石头，自己被摧毁
                isDestroyed = true;
                break;
            case '2':  // 撞上墙，双方都被摧毁
                obj->isDestroyed = true;
                isDestroyed = true;
                break;
            case '3':  // 撞上河流，无事发生
                break;
            case '4':  // 撞上森林，无事发生
                break;
            default:   // 撞上非己方坦克，双方都被摧毁
                if (belong!=obj->id) {
                    obj->isDestroyed = true;
                    isDestroyed = true;
                }
                break;
        }
    }

}
