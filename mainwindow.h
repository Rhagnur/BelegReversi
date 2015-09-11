#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include <QDialog>
#include <QFileDialog>
#include <QTimer>

#include <iostream>
#include <string>

#include "controllerField.h"
#include "viewHS.h"
#include "mydict.h"

#include "ui_mainwindow.h"
#include "ui_gamewidget.h"
#include "ui_menuwidget.h"
#include "ui_pvpwidget.h"
#include "ui_hswidget.h"
#include "ui_optionwidget.h"
#include "ui_pvcwidget.h"

namespace Ui {
class MainWindow;
}

//! Main GUI class
/*!
 * \brief Main class of the GUI
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    //! Constructor
    explicit MainWindow(QWidget *parent = 0);

    //! Deconstructor
    ~MainWindow();

    /*!
     * \brief Needed for resize and Mouseclick event
     * \param target
     * \param event
     * \return bool
     */
    bool eventFilter(QObject *target, QEvent *event);

private slots:

    void timeUp();
    void changeVolume(int value);
    void toggleVolume(bool checked);
    void changeDesign(int design);
    void on_pushButton_IngameBack_clicked();
    void on_pushButton_IngameSkip_clicked();
    void on_pushButton_IngameOptions_clicked();
    void on_pushButton_StartPvP_clicked();
    void on_pushButton_BackPVP_clicked();
    void on_pushButton_StartAI_clicked();
    void on_pushButton_StartGamePvP_clicked();
    void on_pushButton_optionsMenu_clicked();       
    void on_pushButton_Highscore_clicked();
    void on_pushButton_HSBack_clicked();
    void on_pushButton_HSExport_clicked();
    void on_pushButton_OptionBack_clicked();
    void on_pushButton_OptionMusikLoad_clicked();
    void on_comboBox_HSSotieren_activated(int index);
    void on_comboBox_OptionSprache_activated(int index);
    void on_comboBox_PvPGamemode_activated(int index);

    void on_checkBox_OptionVollbild_clicked(bool checked);

    void on_pushButton_StartGamePvC_clicked();

    void on_pushButton_BackPVC_clicked();

    void on_comboBox_PvCGamemode_activated(int index);

private:
    QWidget *menuContainer = new QWidget();
    QWidget *gameContainer = new QWidget();
    QWidget *pvpContainer = new QWidget();
    QWidget *hsContainer = new QWidget();
    QWidget *optionContainer = new QWidget();
    QWidget *pvcContainer = new QWidget();
    QTimer *timer = NULL;

    Ui::MainWindow *mainUI = NULL;
    Ui::GameWidget *gameWidget = NULL;
    Ui::MenuWidget *menuWidget = NULL;
    Ui::PvPWidget *pvpWidget = NULL;
    Ui::HSWidget *hsWidget = NULL;
    Ui::OptionWidget *optionWidget = NULL;
    Ui::PvCWidget *pvcWidget = NULL;

    std::string *myDict = NULL;
    QMediaPlayer *player = NULL;
    QMediaPlaylist *playList = NULL;
    int w = 500,h = 500, offset, design = 0, timePeriod = 1000, timeCount, gameMode = 0;
    bool menuIsInit = false, ingameOptionOn = false;

    MyDict *dict = NULL;
    ViewHS *hsField = NULL;
    controllerField* controllField = NULL;


    void changeLanguage();
    void resizeMainWindow();


};

#endif // MAINWINDOW_H
