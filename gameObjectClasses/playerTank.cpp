//
// Created by WQR on 2023/10/11.
//

#include "playerTank.h"
#include <QDebug>

PlayerTank::PlayerTank(char id_) {
    if (id_=='p') {
        id = 'p';

        imgs[0].load(":/images/m0-0-1.gif");
        imgs[0] = imgs[0].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
        imgs[1].load(":/images/m0-1-1.gif");
        imgs[1] = imgs[1].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
        imgs[2].load(":/images/m0-2-1.gif");
        imgs[2] = imgs[2].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
        imgs[3].load(":/images/m0-3-1.gif");
        imgs[3] = imgs[3].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
    } else {
        id = 'q';

        imgs[0].load(":/images/m1-0-1.gif");
        imgs[0] = imgs[0].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
        imgs[1].load(":/images/m1-1-1.gif");
        imgs[1] = imgs[1].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
        imgs[2].load(":/images/m1-2-1.gif");
        imgs[2] = imgs[2].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
        imgs[3].load(":/images/m1-3-1.gif");
        imgs[3] = imgs[3].scaled(GameDefine::TankWidth, GameDefine::TankHeight);
    }
}

void PlayerTank::Start() {
    if (id=='p') {
        setPos(GameDefine::StartX, GameDefine::StartY);
        setPixmap(imgs[1]);
        direction = 1;
    } else {
        setPos(GameDefine::EnemyStartX[1], GameDefine::EnemyStartY[1]);
        setPixmap(imgs[3]);
        direction = 3;
    }
    isDestroyed = false;
}

void PlayerTank::Update() {
    if (cooldown!=GameDefine::FiringInterval) cooldown -= GameDefine::FrameRate;
    if (cooldown<=0) cooldown = GameDefine::FiringInterval;

    prevFramePos = pos();
    Move();

    // 判断越界
    if (!isOnBound()) setPos(prevFramePos);

    // 判断撞墙
    auto collidedItems = collidingItems();
    GameObject* obstacle = nullptr;
    for (auto item:collidedItems) {
        //  找到与其碰撞的障碍物
        obstacle = (GameObject*)item;
        if (obstacle->id<='3') {  // 即仅检测与石头，墙，河流的碰撞

            // 将其位置重置于单元格中心，并将依此检测碰撞，这样能防止卡墙角，使转弯更为丝滑。
            int standardX = (int)pos().x() / 24 * 24;
            if ((int)pos().x() % 24 > 12) standardX += 24;
            int standardY = (int)pos().y() / 24 * 24;
            if ((int)pos().y() % 24 > 12) standardY += 24;
            setPos(standardX+2, standardY+2);

            break;
        }
    }

    if (obstacle!=nullptr && collidesWithItem(obstacle) && obstacle->id<='3') {
        setPos(prevFramePos);
    }
}

void PlayerTank::Fire(Bullet *bullet) {
    bullet->belong = id;
    bullet->isDestroyed = false;
    bullet->direction = direction;

    // 将子弹位置调整值炮管处
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






