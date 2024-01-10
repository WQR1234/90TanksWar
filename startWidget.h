//
// Created by WQR on 2023/10/9.
//

#ifndef INC_90TANKSWAR_STARTWIDGET_H
#define INC_90TANKSWAR_STARTWIDGET_H

#include <QWidget>
#include <QFile>
#include "chooseScene.h"


QT_BEGIN_NAMESPACE
namespace Ui { class StartWidget; }
QT_END_NAMESPACE

class StartWidget : public QWidget {
Q_OBJECT

public:
    explicit StartWidget(QWidget *parent = nullptr);

    ~StartWidget() override;

private:
    Ui::StartWidget *ui;
    enum Mode {None, Register, SignIn};
    Mode mode = None;

    QFile userInfoFile;
    ChooseScene *chooseScene = nullptr;

    void hideInputControls();
    void showInputControls();

    bool registerAccount();
    bool signInAccount();
};


#endif //INC_90TANKSWAR_STARTWIDGET_H
