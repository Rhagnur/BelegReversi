#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDialog>

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
    controllField->initControllerField(4, ui->graphicsViewField->width(), ui->graphicsViewField->height());
    std::cout << "SetFieldSize to " + std::to_string(ui->graphicsViewField->width()) + " x " + std::to_string(ui->graphicsViewField->height()) << std::endl;
    ui->graphicsViewField->viewport()->installEventFilter(this);

}

void MainWindow::on_pushButton_2_clicked()
{
    //todo
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonPress) {

        QMouseEvent *me = static_cast<QMouseEvent *>(event);
        QPoint coordinates = me->pos();

        controllField->evaluateClick(coordinates.x(), coordinates.y());

        return true;
    }
    if (event->type() == QEvent::Resize)
    {
        controllField->setFieldSize(ui->graphicsViewField->width(), ui->graphicsViewField->height());
        controllField->drawField();
    }

    return false;
}
