//
// Created by WQR on 2023/10/16.
//

#include "stone.h"

Stone::Stone() {
    id = '1';

    imgs[0].load(":/images/stone.gif");
    imgs[0] = imgs->scaled(GameDefine::StillObjectWidth, GameDefine::StillObjectHeight);
    setPixmap(imgs[0]);
}
