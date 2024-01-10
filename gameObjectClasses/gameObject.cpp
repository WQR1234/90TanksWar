//
// Created by WQR on 2023/10/11.
//


#include "gameObject.h"
#include <QDebug>


GameObject::GameObject() {
    setShapeMode(QGraphicsPixmapItem::BoundingRectShape);
}

bool GameObject::isOnBound() const{
    if (this->scenePos().x()>=0 && scenePos().x()<=(624-this->pixmap().width()))
        if (this->scenePos().y()>=0 && scenePos().y()<=(624-this->pixmap().height()))
            return true;
    return false;
}
