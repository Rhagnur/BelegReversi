#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    sceneField = new viewField();
    ui->graphicsViewField->setScene(sceneField);
    ui->graphicsViewField->fitInView(sceneField->sceneRect());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    sceneField->startReversi(ui->graphicsViewField->width(), ui->graphicsViewField->height());
    sceneField->updateFieldSize(ui->graphicsViewField->width(), ui->graphicsViewField->height());

}

void MainWindow::on_pushButton_2_clicked()
{
    //todo
}
