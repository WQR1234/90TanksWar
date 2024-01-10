//
// Created by WQR on 2023/10/14.
//

#ifndef INC_90TANKSWAR_GAMEDEFINE_H
#define INC_90TANKSWAR_GAMEDEFINE_H

#include <QTimer>
#include <QList>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QPixmap>


class GameDefine {
public:
    static const int FrameRate = 40;  // 帧率 (单位：ms)
    static const int SceneWidth = 624;  //  屏幕宽度  (单位： 像素)
    static const int SceneHeight = 624;  //  屏幕高度

    static const int TankWidth = 44;   // 坦克宽度， 本应为48，左右空2px防止卡墙
    static const int TankHeight = 44;  // 坦克高度， 本应为48，上下空2px防止卡墙
    static const int BulletWidth = 16;  // 子弹宽度
    static const int BulletHeight = 16;  // 子弹高度
    static const int StillObjectWidth = 24;  // 静物（石头，墙等）宽度 , 也即单元格宽度
    static const int StillObjectHeight = 24;  // 静物（石头，墙等）高度， 也即单元格高度

    static const int EnemyTankNum = 12;  // 总敌方坦克数

    // 玩家坦克起点
    static const int StartX = 9*24+2;
    static const int StartY = 24*24+2;
    static const int FiringInterval = 800;  // 敌方坦克子弹发射时间间隔 0.8s

    // 敌方坦克的3个起点
    static const int EnemyStartX[3];
    static const int EnemyStartY[3];

    static const int MaxLevel = 3;  // 最大关卡数

    //  多个地图矩阵 （26×26）
    static const char MAPS[10][26][27];
};


#endif //INC_90TANKSWAR_GAMEDEFINE_H
