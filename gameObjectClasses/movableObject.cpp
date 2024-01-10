//
// Created by WQR on 2023/10/11.
//

#include "movableObject.h"


MovableObject::MovableObject() {

}

void MovableObject::Move() {
    int x=0, y=0;
    switch (direction) {
        case 0:
            x = -1; y = 0;
            break;
        case 1:
            x = 0; y = -1;
            break;
        case 2:
            x = 1; y = 0;
            break;
        case 3:
            x = 0; y = 1;
            break;
        default:
            break;
    }
    this->moveBy(x*speed, y*speed);
}

void MovableObject::Update() {

}
