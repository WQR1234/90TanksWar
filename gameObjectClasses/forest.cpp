//
// Created by WQR on 2023/10/16.
//

#include "forest.h"

Forest::Forest() {
    id = '4';

    imgs[0].load(":/images/forest.gif");
    imgs[0] = imgs[0].scaled(GameDefine::StillObjectWidth, GameDefine::StillObjectHeight);
    setPixmap(imgs[0]);

    setZValue(10);  // 设置z轴坐标，默认值为0，设为10可使其在发生重叠时，总是在其他QGraphicsItem上方。
}
