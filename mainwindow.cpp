#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reversiField = new controllerField(6);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startReversi()
{
    reversiField->startGame();
}
