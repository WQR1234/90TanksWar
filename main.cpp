#include <QApplication>
#include "startWidget.h"
#include "gameWidget.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    StartWidget w;
    w.show();
    return QApplication::exec();
}
