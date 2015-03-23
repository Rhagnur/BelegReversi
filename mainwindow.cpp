#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    controllField = new controllerField();
    ui->graphicsViewField->setScene(controllField->passViewField());
    //ui->graphicsViewField->fitInView(controllField->passViewField()->sceneRect());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "Startbutton gedrueckt" << std::endl;
    controllField->initControllerField(6, ui->graphicsViewField->width(), ui->graphicsViewField->height());
    std::cout << "SetFieldSize to " + std::to_string(ui->graphicsViewField->width()) + " x " + std::to_string(ui->graphicsViewField->height()) << std::endl;
    //sceneField->startReversi(ui->graphicsViewField->width(), ui->graphicsViewField->height());
    //sceneField->updateFieldSize(ui->graphicsViewField->width(), ui->graphicsViewField->height());

}

void MainWindow::on_pushButton_2_clicked()
{
    //todo
}
