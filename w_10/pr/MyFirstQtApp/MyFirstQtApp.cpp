#include "MyFirstQtApp.h"
#include "ui_MyFirstQtApp.h"

MyFirstQtApp::MyFirstQtApp(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MyFirstQtApp)
{
    ui->setupUi(this);
}

MyFirstQtApp::~MyFirstQtApp()
{
    delete ui;
}

