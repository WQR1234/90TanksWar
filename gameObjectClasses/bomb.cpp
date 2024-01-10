//
// Created by My on 2023/10/17.
//

#include "bomb.h"
#include <QRandomGenerator>

Bomb::Bomb() {
    id = 'o';

    imgs[0].load(":/images/bumb1.gif");
    imgs[1].load(":/images/bumb2.gif");
    imgs[2].load(":/images/bumb3.gif");

    int i = QRandomGenerator::global()->bounded(3);
    setPixmap(imgs[i]);
    setZValue(1);
}

void Bomb::Update() {
    life -= GameDefine::FrameRate;
    if (life<=0) isDestroyed = true;
}
