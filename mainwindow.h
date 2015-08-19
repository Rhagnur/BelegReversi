#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
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
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();

    void on_pushButton_Start_clicked();

    void on_pushButton_optionsMenu_clicked();

    void on_pushButton_3_clicked();

    void changeVolume(int value);
    void toggleVolume(bool checked);
    void changeDesign(int design);

    void on_pushButton_StartAI_clicked();

private:
    QWidget *menuContainer = new QWidget();
    QWidget *gameContainer = new QWidget();
    Ui::MainWindow *mainUI;
    Ui::GameWidget *gameWidget;
    Ui::MenuWidget *menuWidget;
    controllerField* controllField;
    menu* myMenu;
    bool menuIsInit = false, ingameOptionOn = false;
    QMediaPlayer *player;
    QMediaPlaylist *playList;

};

#endif // MAINWINDOW_H
