//
// Created by WQR on 2023/10/10.
//

// You may need to build the project (run Qt uic code generator) to get "ui_ChooseScene.h" resolved

#include "chooseScene.h"
#include "ui_ChooseScene.h"
#include <QMessageBox>
#include <QJsonArray>
#include <QJsonDocument>


ChooseScene::ChooseScene(QWidget *parent) :
        QWidget(parent), ui(new Ui::ChooseScene) {
    ui->setupUi(this);

    userInfoFile.setFileName("./database/users_info.json");

    gameWidget = new GameWidget;

    //  Player按钮连到单人模式
    connect(ui->singleBtn, &QPushButton::clicked, this, [=](){
        GameControl::Instance()->mode = GameControl::Single;
        gameWidget->chooseSingleMode();
        QTimer::singleShot(500, this, [=](){
            this->hide();
            gameWidget->show();
            GameControl::Instance()->Awake();
        });
    });

    //  Players按钮连到双人模式
    connect(ui->doubleBtn, &QPushButton::clicked, this, [=](){
        GameControl::Instance()->mode = GameControl::Double;
        gameWidget->chooseDoubleMode();
        QTimer::singleShot(500, this, [=](){
            this->hide();
            gameWidget->show();
            GameControl::Instance()->Awake();
        });
    });

    //  Info按钮连到信息查看
    connect(ui->infoBtn, &QPushButton::clicked, this, [=](){
        //  以只读的方式打开json文件
        if (!userInfoFile.open(QFile::ReadOnly | QFile::Text)) {
            qDebug() << "can't open error!";
            return;
        }

        //  读取json文件，拿到json对象
        QTextStream stream(&userInfoFile);
        stream.setCodec("UTF-8");
        QString str = stream.readAll();
        userInfoFile.close();
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject datas = doc.object();

        QMessageBox msgBox(QMessageBox::NoIcon, "user information", "");
        msgBox.setFixedSize(300, 300);
        msgBox.setText("user name: "+userName+'\n'+
                        "times(s):"+ "\nLevel1: "+QString::number(datas[userName].toObject().value("times").toArray().at(0).toInt())+
                               "\nLevel2: "+QString::number(datas[userName].toObject().value("times").toArray().at(1).toInt())+
                               "\nLevel3: "+QString::number(datas[userName].toObject().value("times").toArray().at(2).toInt()));

        msgBox.setStyleSheet(QString::fromUtf8("color:rgb(255, 170, 0);\n""font: 10pt \"Microsoft YaHei\";\n""background-color:black;"));
        msgBox.exec();
    });

    // previous page按钮返回上一窗口
    connect(ui->returnBtn, &QPushButton::clicked, this, [=](){
       emit returnPrevPage();
    });

    // gameWidget的recordTime信号将修改json文件中对应用户名的times数据
    connect(gameWidget, &GameWidget::recordTime, this, [=](){
        //  以读写的方式打开json文件
        if (!userInfoFile.open(QFile::ReadWrite)) {
            qDebug() << "can't open error!";
            return;
        }

        //  读取json文件，拿到json对象
        QTextStream stream(&userInfoFile);
        stream.setCodec("UTF-8");
        QString str = stream.readAll();
        userInfoFile.seek(0);
        QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
        QJsonObject datas = doc.object();

        QJsonObject userInfo = datas.value(userName).toObject();
        QJsonArray times = userInfo.value("times").toArray();

        // 修改相应的times数据为通关时间
        if (GameControl::Instance()->level<=3) {
            int sec = times[GameControl::Instance()->level-1].toInt();
            if (sec==-1 || sec>GameControl::Instance()->totalSec)
                times[GameControl::Instance()->level-1] = GameControl::Instance()->totalSec;
        }

        userInfo["times"] = times;
        datas[userName] = userInfo;

        doc.setObject(datas);
        stream << doc.toJson();
        userInfoFile.close();
    });

    // gameWidget的returnPrevPage将返回至此窗口
    connect(gameWidget, &GameWidget::returnPrevPage, this, [=](){
        gameWidget->hide();
        this->show();
    });
}

ChooseScene::~ChooseScene() {
    delete ui;
}
