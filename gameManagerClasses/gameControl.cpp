//
// Created by WQR on 2023/10/11.
//

#include "gameControl.h"
// #include "gameObjectPool.h"
#include "enemyTank.h"
#include "stone.h"
#include "forest.h"
#include "bomb.h"

#include <QDebug>
#include <QRandomGenerator>



GameControl* GameControl::instance = nullptr;

GameControl::GameControl() {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, [=](){
        Update();
    });

    // Awake();
    
}

void GameControl::Awake() {
//    // 对象池初始化(仅第一次进入游戏时需要)
//    if (!isPoolInit) {
//        GameObjectPool::Instance()->initPool();
//        GameObjectPool::Instance()->setParent(this);
//        isPoolInit = true;
//    }

    // 初始化玩家坦克
    player = new PlayerTank();
    player->Start();
    scene->addItem(player);

    // 初始化营地 （仅单人模式）
    if (mode==Single) {
        camp = new Camp;
        camp->setPos(12 * 24 + 2, 24 * 24 + 2);
        scene->addItem(camp);
    } else {
        camp = nullptr;
    }

    // 初始化玩家坦克2 （仅双人模式）
    if (mode==Double) {
        player2 = new PlayerTank('q');
        player2->Start();
        scene->addItem(player2);
    } else {
        player2 = nullptr;
    }

    loadMap();
    totalSec = 0;

    timer->start(GameDefine::FrameRate);
}

void GameControl::Update() {

    //  判断基地被摧毁
    if (mode==Single) {
        if (camp != nullptr && camp->isDestroyed) {
            Reset(false);
            emit gameOver();
            return;
        }
    }

    // 所有敌人被消灭，进入下一关
    if (totalEnemyNum==0 && enemyNumInScene==0) {
        Reset(true);
        emit victory();
        return;
    }

    //  更新所有可动游戏对象的位置
    player->Update();
    if (mode==Double) player2->Update();
    for (auto go: allMovableObjects) {
        go->Update();
    }

    //  判断玩家是否被摧毁
    if (player->isDestroyed) {
        player->blood --;
        if (player->blood==0) {
            Reset(false);
            if (mode==Single) emit gameOver();
            else emit gameOver(1);
            return;
        } else {
            player->Start();
            emit loseBlood(1);
        }
    }

    //  判断玩家2是否被摧毁

    if (player2 != nullptr && player2->isDestroyed) {
        player2->blood--;
        if (player2->blood == 0) {
            Reset(false);
            emit gameOver(2);
            return;
        } else {
            player2->Start();
            emit loseBlood(2);
        }
    }


    // 移除所有被摧毁的可动对象
    for (auto go: allMovableObjects) {
        if (go->isDestroyed) {
            if (go->id=='b' || go->id=='e' || go->id=='o') {
                // GameObjectPool::Instance()->recoveryGameObject(go);
                if (go->id=='e') {
                    enemyNumInScene--;
                    emit killOne();
                }
                else if (go->id=='b') {
                    // auto bomb = (Bomb*) GameObjectPool::Instance()->getGameObject('o');
                    auto bomb = new Bomb;
                    bomb->setPos(go->pos());
                    scene->addItem(bomb);
                    allMovableObjects.append(bomb);
                }
            }
            scene->removeItem(go);
            allMovableObjects.removeOne(go);
            // delete go;
        }
    }

    // 移除所有被摧毁的墙
    for (auto w:allWalls) {
        if (w->isDestroyed) {
            scene->removeItem(w);
            allWalls.removeOne(w);
            // GameObjectPool::Instance()->recoveryGameObject(w);
            // delete w;
        }
    }

    // 每5秒且场上少于4个时，生成一个敌方坦克 (仅单人模式)
    if (mode==Single) {
        cnt += GameDefine::FrameRate;
        if (cnt >= 1000) {
            cnt = 0;
            totalSec++;
            if (totalSec % 5 == 1) {
                if (enemyNumInScene < 4 && totalEnemyNum > 0) generateEnemyTank();
            }
        }
    }


}

void GameControl::generateEnemyTank() {
    // auto enemy = (EnemyTank*)GameObjectPool::Instance()->getGameObject('e');
    auto enemy = new EnemyTank;
    allMovableObjects.append(enemy);
    int posIdx = QRandomGenerator::global()->bounded(3);  // 随机一个位置的索引
    enemy->setPos(GameDefine::EnemyStartX[posIdx], GameDefine::EnemyStartY[posIdx]);
    scene->addItem(enemy);

    // 若当前位置已有坦克，即发生碰撞，则重新生成一个位置索引
    while (!enemy->collidingItems().empty()) {
        posIdx = QRandomGenerator::global()->bounded(3);
        enemy->setPos(GameDefine::EnemyStartX[posIdx], GameDefine::EnemyStartY[posIdx]);
    }

    // 场上坦克数加1，剩余坦克数减1
    enemyNumInScene ++;
    totalEnemyNum --;
}

void GameControl::loadMap() {
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            GameObject *obj = nullptr;
            switch (GameDefine::MAPS[level][i][j]) {
                case '1':
                    obj = new Stone;
                    break;
                case '2':
                    // obj = (Wall*)GameObjectPool::Instance()->getGameObject('2');
                    obj = new Wall;
                    break;
                case '4':
                    obj = new Forest;
                    break;
                default:
                    break;
            }
            if (obj!= nullptr) {
                obj->setPos(j*GameDefine::StillObjectWidth, i*GameDefine::StillObjectHeight);
                scene->addItem(obj);
                if (obj->id=='2') allWalls.append((Wall*)obj);
            }

        }
    }
}

void GameControl::recoveryAllObjects() {
    scene->clear();
//    for (auto go:allMovableObjects) {
//        GameObjectPool::Instance()->recoveryGameObject(go);
//    }
//    for (auto w: allWalls) {
//        GameObjectPool::Instance()->recoveryGameObject(w);
//    }

    allMovableObjects.clear();
    allWalls.clear();
}

void GameControl::Reset(bool isVictory) {
    level = isVictory ? level+1 : 0;

    timer->stop();
    player = nullptr; camp = nullptr; player2= nullptr;
    recoveryAllObjects();
    totalEnemyNum = GameDefine::EnemyTankNum;
    cnt = 0;
}






