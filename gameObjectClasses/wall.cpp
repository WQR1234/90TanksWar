//
// Created by WQR on 2023/10/15.
//

#include "wall.h"
#include "gameDefine.h"

Wall::Wall() {
    id = '2';

    imgs[0].load(":/images/wall.gif");
    imgs[0] = imgs->scaled(GameDefine::StillObjectWidth, GameDefine::StillObjectHeight);
    setPixmap(imgs[0]);

}
