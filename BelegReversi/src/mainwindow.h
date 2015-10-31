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
/*!
 * \author Jan Didschuneit
 */
namespace Ui {
class MainWindow;

/*! \mainpage Reversi the game
 *
 * \section author_sec Autoren
 *
 * Jan Didschuneit (s0539714) \n
 * Baran Özyüzücüler (s0540255)
 *
 * \section overview_sec Übersicht
 *
 * Dieser Beleg umfasst die Projektierung, Realisierung und Programmierung des Spiels Reversi unter den gestellten Anforderungen des Dozenten. \n
 * Die Anforderungen selbst sind der ausgehändigten PDF zu entnehmen und werden nicht noch einmal genauer beschrieben hier.\n\n
 *
 * \section technial_sec Technische Daten
 *
 * Benötigte Software und Packages zum Kompilieren und Testen:\n\n
 *
 * Programmierumgebung\n
 * - Ubuntu 14.10\n
 * - QT 5.5\n
 * - QT Creator 3.5.0\n\n
 * .
 * Valgrind\n
 * - "valgrind" Package\n\n
 * .
 * Doxygen\n
 * - "doxygen" und "graphviz" Packages\n\n
 * .
 * Android Testing\n
 * - Android für x86 (GCC 4.9, QT 5.5.0)
 * - Android Studio 1.3.2 with Android SDK
 * - Android NDK r10e
 * - Galaxy_Nexus_API_15 Virtual Device (API 15, CPU/ABI x86)\n\n
 * .
 * Windows (Docker) Testing\n
 * - siehe txt Datei in Dokumentation/Docker\n
 * .
 */
}

//! Main GUI class
/*!
 * \brief Handling all the GUI stuff
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

    QString *myDict = NULL;
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
