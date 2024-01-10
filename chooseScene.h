//
// Created by WQR on 2023/10/10.
//

#ifndef INC_90TANKSWAR_CHOOSESCENE_H
#define INC_90TANKSWAR_CHOOSESCENE_H

#include <QWidget>
#include <QString>
#include <QJsonObject>
#include <QFile>
#include <QDebug>
#include "gameWidget.h"


QT_BEGIN_NAMESPACE
namespace Ui { class ChooseScene; }
QT_END_NAMESPACE

class ChooseScene : public QWidget {
Q_OBJECT

public:
    QString userName;

    explicit ChooseScene(QWidget *parent = nullptr);

    ~ChooseScene() override;

private:
    Ui::ChooseScene *ui;

    GameWidget * gameWidget;

    QFile userInfoFile;

signals:
    void returnPrevPage();
};


#endif //INC_90TANKSWAR_CHOOSESCENE_H
