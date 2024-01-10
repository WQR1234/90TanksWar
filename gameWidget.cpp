//
// Created by WQR on 2023/10/11.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GameWidget.h" resolved

#include "gameWidget.h"
#include "playerTank.h"
// #include "gameObjectPool.h"
#include "bullet.h"

#include "ui_GameWidget.h"
#include <QKeyEvent>
#include <QDebug>


GameWidget::GameWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::GameWidget) {
    ui->setupUi(this);
    setFixedSize(this->size());
    ui->ggLabel->hide();  //  隐藏游戏结束标签
    ui->vLabel->hide();   //  隐藏胜利标签

    // setFocusPolicy(Qt::StrongFocus);  // 只有加上这句话才能监听到4个箭头按键 (TM为啥没用)

    //  收到游戏结束信号，则显示游戏结束标签
    connect(GameControl::Instance(), &GameControl::gameOver, this, [=](int i){
        if (i==1) ui->ggLabel->setText("Green Win");
        else if (i==2) ui->ggLabel->setText("Yellow Win");
        ui->ggLabel->show();

        QTimer::singleShot(3000, this, [=](){
            ui->ggLabel->hide();
            emit returnPrevPage();

        });
    });

    //  收到游戏胜利信号，则显示游戏胜利标签，并在3秒后进入下一关
    connect(GameControl::Instance(), &GameControl::victory, this, [=](){
        ui->vLabel->show();
        emit recordTime();
        GameControl::Instance()->totalSec = 0;

        QTimer::singleShot(3000, this, [=](){
            ui->vLabel->hide();
            ui->enemyNumLable->setText("12");
            ui->playerBloodNumLabel->setText("3");
            if (GameControl::Instance()->level<GameDefine::MaxLevel) {
                GameControl::Instance()->Awake();
            } else {
                GameControl::Instance()->level = 0;
                emit returnPrevPage();
            }
        });

    });

    //  收到击杀一个敌人信号，则修改剩余敌方坦克数
    connect(GameControl::Instance(), &GameControl::killOne, this, [=](){
        QString s = ui->enemyNumLable->text();
        int num = s.toInt() - 1;
        ui->enemyNumLable->setText(std::to_string(num).c_str());
    });

    connect(GameControl::Instance(), &GameControl::loseBlood, this, [=](int i){
        if (i==1) {
            int blood = ui->playerBloodNumLabel->text().toInt() - 1;
            ui->playerBloodNumLabel->setText(QString::number(blood));
        } else if (i==2) {
            int blood = ui->enemyNumLable->text().toInt() - 1;
            ui->enemyNumLable->setText(QString::number(blood));
        }
    });

    // 设置QGraphicsScene
    gameScene = new QGraphicsScene(this);

   // ui->graphicsView->setSceneRect(0, 0, 624, 624);
   gameScene->setSceneRect(0, 0, 624, 624);
    ui->graphicsView->setScene(gameScene);
    GameControl::Instance()->scene = gameScene;
    GameControl::Instance()->setParent(this);

//    GameControl::Instance()->Awake();
    ui->graphicsView->show();

}

GameWidget::~GameWidget() {
    delete ui;
}

//  方向键按下，则速度设为6； 方向键松开，则速度设为0
void GameWidget::keyPressEvent(QKeyEvent *event) {
    auto player = GameControl::Instance()->player;
    if (player == nullptr) return;
    int dir = -1;  // 新的方向
    switch (event->key()) {
        case Qt::Key_A:
            dir = 0;
            break;
        case Qt::Key_W:
            dir = 1;
            break;
        case Qt::Key_D:
            dir = 2;
            break;
        case Qt::Key_S:
            dir = 3;
            break;
        default:
            break;
    }
    if (dir!=-1) {
        player->speed = 6;
        // 若与之前方向不一样，则更新图片
        if (player->direction!=dir) {
            player->direction = dir;
            player->setPixmap(player->imgs[dir]);
        }
    }
    //  开火
    if (event->key()==Qt::Key_J && player->cooldown==GameDefine::FiringInterval) {
        player->cooldown -= GameDefine::FrameRate;
        // auto bullet = (Bullet*)GameObjectPool::Instance()->getGameObject('b');
        auto bullet = new Bullet;
        player->Fire(bullet);
        gameScene->addItem(bullet);
        GameControl::Instance()->allMovableObjects.append(bullet);
    }

    //  双人模式下的玩家2 (代码除了键盘按键外与上相同)
    auto player2 = GameControl::Instance()->player2;
    if (player2== nullptr) return;
    dir = -1;  // 新的方向
    switch (event->key()) {
        case Qt::Key_1:
            dir = 0;
            break;
        case Qt::Key_5:
            dir = 1;
            break;
        case Qt::Key_3:
            dir = 2;
            break;
        case Qt::Key_2:
            dir = 3;
            break;
        default:
            break;
    }
    if (dir!=-1) {
        player2->speed = 6;

        // 若与之前方向不一样，则更新图片
        if (player2->direction!=dir) {
            player2->direction = dir;
            player2->setPixmap(player2->imgs[dir]);
        }
    }
    //  开火
    if (event->key()==Qt::Key_0 && player2->cooldown==GameDefine::FiringInterval) {
        player2->cooldown -= GameDefine::FrameRate;
        // auto bullet = (Bullet*)GameObjectPool::Instance()->getGameObject('b');

        auto bullet = new Bullet;
        player2->Fire(bullet);
        gameScene->addItem(bullet);
        GameControl::Instance()->allMovableObjects.append(bullet);
    }
}

void GameWidget::keyReleaseEvent(QKeyEvent *event) {
    auto player = GameControl::Instance()->player;
    if (player== nullptr) return;
    switch (event->key()) {
        case Qt::Key_A:
        case Qt::Key_W:
        case Qt::Key_D:
        case Qt::Key_S:
            player->speed = 0;
            break;
    }

    auto player2 = GameControl::Instance()->player2;
    if (player2== nullptr) return;
    switch (event->key()) {
        case Qt::Key_1:
        case Qt::Key_5:
        case Qt::Key_3:
        case Qt::Key_2:
            player2->speed = 0;
            break;
    }
}

void GameWidget::chooseSingleMode() {
    ui->ggLabel->setText("Game Over");
    ui->enemyLabel->setText("Remaining Enemy:");
    ui->enemyNumLable->setText("12");
}

void GameWidget::chooseDoubleMode() {
    ui->enemyLabel->setText("Player2 Blood:");
    ui->enemyNumLable->setText("3");
}
