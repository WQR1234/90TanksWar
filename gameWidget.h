//
// Created by WQR on 2023/10/11.
//

#ifndef INC_90TANKSWAR_GAMEWIDGET_H
#define INC_90TANKSWAR_GAMEWIDGET_H

#include <QWidget>
#include <QGraphicsScene>
#include <QKeyEvent>
#include "gameControl.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GameWidget; }
QT_END_NAMESPACE

class GameWidget : public QWidget {
Q_OBJECT

public:
    explicit GameWidget(QWidget *parent = nullptr);

    ~GameWidget() override;

    QGraphicsScene *gameScene;

    void chooseSingleMode();
    void chooseDoubleMode();

private:
    Ui::GameWidget *ui;

protected:
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;

signals:
    void recordTime();
    void returnPrevPage();
};


#endif //INC_90TANKSWAR_GAMEWIDGET_H
