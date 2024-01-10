//
// Created by WQR on 2023/10/9.
//

// You may need to build the project (run Qt uic code generator) to get "ui_StartWidget.h" resolved

#include "startWidget.h"
#include "ui_StartWidget.h"
#include <QTextStream>
#include <QString>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonValue>
#include <QJsonParseError>
#include <QTimer>

#include <QDebug>


StartWidget::StartWidget(QWidget *parent) :
        QWidget(parent), ui(new Ui::StartWidget) {
    ui->setupUi(this);
    this->setFixedSize(this->size());
    hideInputControls();

    userInfoFile.setFileName("./database/users_info.json");

    //  注册按钮
    connect(ui->registerBtn, &QPushButton::clicked, this, [=](){
        showInputControls();
        mode = Register;
    });

    //  登录按钮
    connect(ui->signinBtn, &QPushButton::clicked, this, [=](){
        showInputControls();
        mode = SignIn;
    });

    // 取消按钮
    connect(ui->cancelBtn, &QPushButton::clicked, this, [=](){
        hideInputControls();
        ui->unEdit->clear();
        ui->pwEdit->clear();
        ui->infoEdit->clear();
        mode = None;
    });

    chooseScene = new ChooseScene;

    //  确定按钮
    connect(ui->okBtn, &QPushButton::clicked, this, [=](){
        switch (mode) {
            case Register:
                if (registerAccount()) {
                    ui->infoEdit->setText("Register Success");
                } else {
                    ui->infoEdit->setText("User name already exists");
                }
                break;
            case SignIn:
                if (signInAccount()) {
                    ui->infoEdit->setText("Sign In Success");
                    QTimer::singleShot(1000, this, [=](){
                        this->hide();
                        chooseScene->show();
                    });

                } else {
                    ui->infoEdit->setText("Incorrect username or password");
                }
                break;
            case None:
                break;
        }
    });

    //  接收chooseScene窗口的返回信号，返回此窗口
    connect(chooseScene, &ChooseScene::returnPrevPage, this, [=](){
       chooseScene->hide();
        this->show();
        ui->cancelBtn->click();
    });
}

StartWidget::~StartWidget() {
    delete ui;
}

void StartWidget::hideInputControls() {
    ui->unLabel->hide();
    ui->unEdit->hide();
    ui->pwLabel->hide();
    ui->pwEdit->hide();
    ui->okBtn->hide();
    ui->cancelBtn->hide();
}

void StartWidget::showInputControls() {
    ui->unLabel->show();
    ui->unEdit->show();
    ui->pwLabel->show();
    ui->pwEdit->show();
    ui->okBtn->show();
    ui->cancelBtn->show();
}

bool StartWidget::registerAccount() {
    //  以读写的方式打开json文件
    if (!userInfoFile.open(QFile::ReadWrite)) {
        qDebug() << "can't open error!";
        return false;
    }

    //  读取json文件，拿到json对象
    QTextStream stream(&userInfoFile);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();
    userInfoFile.seek(0);
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject datas = doc.object();

    //  拿到文本框输入的用户名
    QString userName = ui->unEdit->text();

    //  若已包含用户名这个键,则不能继续注册
    if (datas.contains(userName)) {
        userInfoFile.close();
        return false;
    }

    // 写入json  键：用户名， 值：密码，时间记录
    QString password = ui->pwEdit->text();
    QJsonObject newUser;
    QJsonArray times = {-1, -1, -1};
    newUser.insert("password", password);
    newUser.insert("time", times);

    datas.insert(userName, newUser);
    doc.setObject(datas);

    stream << doc.toJson();
    userInfoFile.close();

    return true;
}

bool StartWidget::signInAccount() {
    //  以只读的方式打开json文件
    if (!userInfoFile.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "can't open error!";
        return false;
    }

    //  读取json文件，拿到json对象
    QTextStream stream(&userInfoFile);
    stream.setCodec("UTF-8");
    QString str = stream.readAll();
    userInfoFile.close();
    QJsonDocument doc = QJsonDocument::fromJson(str.toUtf8());
    QJsonObject datas = doc.object();

    QString userName = ui->unEdit->text();
    QString password = ui->pwEdit->text();

    //  若包含用户名，且密码正确，则登录成功
    if (datas.contains(userName)) {
        if (datas[userName].toObject().value("password")==password) {
            chooseScene->userName = userName;
            return true;
        }
    }
    return false;
}


