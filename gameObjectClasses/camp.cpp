//
// Created by My on 2023/10/16.
//

#include "camp.h"

Camp::Camp() {
    id = 'c';

    imgs[0].load(":/images/camp0.gif");
    imgs[0] = imgs[0].scaled(GameDefine::TankWidth, GameDefine::TankHeight);

    setPixmap(imgs[0]);

}
