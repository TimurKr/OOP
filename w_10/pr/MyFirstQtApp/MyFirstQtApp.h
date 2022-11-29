#ifndef MYFIRSTQTAPP_H
#define MYFIRSTQTAPP_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MyFirstQtApp; }
QT_END_NAMESPACE

class MyFirstQtApp : public QMainWindow
{
    Q_OBJECT

public:
    MyFirstQtApp(QWidget *parent = nullptr);
    ~MyFirstQtApp();

private:
    Ui::MyFirstQtApp *ui;
};
#endif // MYFIRSTQTAPP_H
