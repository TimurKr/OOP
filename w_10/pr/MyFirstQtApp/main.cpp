#include "MyFirstQtApp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyFirstQtApp w;
    w.show();
    return a.exec();
}
