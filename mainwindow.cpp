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
    ui->labelPlayer1->setText(QString::fromStdString(sceneField->returnTestStringXY()));
    std::cout<<"GroesseView = " + std::to_string(ui->graphicsViewField->width()) + " x " + std::to_string(ui->graphicsViewField->height()) << std::endl;
    std::cout<<"GroesseScene = " + std::to_string(sceneField->width()) + " x " + std::to_string(sceneField->height()) << std::endl;
}
