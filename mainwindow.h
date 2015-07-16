#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include "controllerField.h"
#include "ui_mainwindow.h"
#include "ui_gamewidget.h"
#include "ui_menuwidget.h"
#include "menu.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    //void on_pushButton_clicked();
    //void on_pushButton_2_clicked();
    //void on_pushButton_3_clicked();

private:
    QWidget *menuContainer = new QWidget();
    QWidget *gameContainer = new QWidget();
    Ui::MainWindow *mainUI;
    Ui::GameWidget *gameWidget;
    Ui::MenuWidget *menuWidget;
    controllerField* controllField;
    menu* myMenu;
    bool menuIsInit = false;
};

#endif // MAINWINDOW_H
