//
// Created by WQR on 2023/10/11.
//

#ifndef INC_90TANKSWAR_MOVABLEOBJECT_H
#define INC_90TANKSWAR_MOVABLEOBJECT_H

#include "gameObject.h"



class MovableObject: public GameObject {
public:
    int direction = 0;  // 0: 左, 1: 上, 2: 右, 3: 下
    int speed = 0;

    MovableObject();

    virtual void Update();

protected:


    void Move();

};


#endif //INC_90TANKSWAR_MOVABLEOBJECT_H
