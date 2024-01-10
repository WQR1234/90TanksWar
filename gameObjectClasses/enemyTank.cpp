//
// Created by WQR on 2023/10/14.
//

#include "enemyTank.h"
// #include "gameObjectPool.h"
#include "bullet.h"
#include "gameControl.h"
#include <QRandomGenerator>
#include <QDebug>


EnemyTank::EnemyTank() {
    id = 'e';

    imgs[0].load(":/images/1-1-1.gif");
    imgs[0] = imgs[0].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
    imgs[1].load(":/images/1-2-1.gif");
    imgs[1] = imgs[1].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
    imgs[2].load(":/images/1-3-1.gif");
    imgs[2] = imgs[2].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
    imgs[3].load(":/images/1-4-1.gif");
    imgs[3] = imgs[3].scaled(GameDefine::TankWidth, GameDefine::TankHeight);

    this->setPixmap(imgs[3]);
    direction = 3;
    speed = 6;

}

void EnemyTank::Update() {
    prevFramePos = pos();
    Move();

    // 若触碰边界，则转向（随机）。
    if (!isOnBound()) {
        setPos(prevFramePos);
        direction = QRandomGenerator::global()->bounded(4);
        setPixmap(imgs[direction]);
    }

    // 若撞墙，则转向（随机）。
    auto collidedItems = collidingItems();
    GameObject* obstacle = nullptr;
    for (auto item:collidedItems) {
        //  找到与其碰撞的障碍物
        obstacle = (GameObject*)item;
        if (obstacle->id<='3' || obstacle->id=='e') {

            setPos(prevFramePos);
            direction = QRandomGenerator::global()->bounded(4);
            setPixmap(imgs[direction]);
            break;
        }
    }

    // 若到1秒，则发射子弹
    cnt += GameDefine::FrameRate;
    if (cnt>=GameDefine::FiringInterval) {
        cnt = 0;
        // auto bullet = (Bullet*)GameObjectPool::Instance()->getGameObject('b');
        auto bullet = new Bullet;
        Fire(bullet);
        GameControl::Instance()->scene->addItem(bullet);
        GameControl::Instance()->allMovableObjects.append(bullet);
    }
    
    //
}

void EnemyTank::Fire(Bullet *bullet) {
    bullet->isDestroyed = false;
    bullet->belong = id;
    bullet->direction = direction;
    double x = pos().x(), y = pos().y();
    switch (direction) {
        case 0:
            y += (GameDefine::TankHeight- GameDefine::BulletHeight) / 2.0f;
            break;
        case 1:
            x += (GameDefine::TankWidth - GameDefine::BulletWidth) / 2.0f;
            break;
        case 2:
            y += (GameDefine::TankHeight- GameDefine::BulletHeight) / 2.0f;
            x += GameDefine::TankWidth - GameDefine::BulletWidth/2 ;
            break;
        case 3:
            x += (GameDefine::TankWidth - GameDefine::BulletWidth) / 2.0f;
            y += GameDefine::TankHeight-GameDefine::BulletHeight/2;
            break;
    }
    bullet->setPos(x, y);
    bullet->setPixmap(bullet->imgs[direction]);
}


