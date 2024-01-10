//
// Created by WQR on 2023/10/11.
//

#ifndef INC_90TANKSWAR_GAMECONTROL_H
#define INC_90TANKSWAR_GAMECONTROL_H

#include <QSet>
#include "gameDefine.h"

#include "movableObject.h"
#include "playerTank.h"
#include "wall.h"
#include "camp.h"


class GameControl: public QObject{
Q_OBJECT

public:
    enum GameMode {Single, Double};
    GameMode mode = Single;

    QGraphicsScene* scene;

    GameControl();

    static GameControl* Instance() {
        if (instance == nullptr) return instance = new GameControl;
        else return instance;
    }

    QList<MovableObject*> allMovableObjects = {};
    QList<Wall*> allWalls = {};

    bool isPoolInit = false;
    void Awake();
    void Update();

    void Reset(bool isVictory);

    PlayerTank* player = nullptr;
    PlayerTank* player2 = nullptr;  //  双人模式下的另一个坦克

    int totalSec = 0;  // 记录游戏开始了多长时间（单位：秒）
    int level = 0;   //  当前关卡数

private:
    static GameControl* instance;

    QTimer *timer;

    int cnt = 0;

    int enemyNumInScene = 0;  // 场上的敌方坦克数
    int totalEnemyNum = GameDefine::EnemyTankNum;   // 总共（剩下）的敌方坦克数

    Camp* camp = nullptr;



    void loadMap();   // 加载地图
    void generateEnemyTank();
    void recoveryAllObjects();



signals:
    void gameOver(int i=0);
    void victory();
    void killOne();
    void loseBlood(int i);

};


#endif //INC_90TANKSWAR_GAMECONTROL_H
