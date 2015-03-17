#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "controllerField.h"
#include "viewField.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void startReversi();

private slots:
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    controllerField* reversiField;
    viewField* sceneField;
};

#endif // MAINWINDOW_H
