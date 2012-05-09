#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <database.h>
GestType *ListType;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ListType = new GestType();
    ListType->LoadFromFile(new QString(QDir::currentPath()+"/conf/type.dat"));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_pressed()
{
}
