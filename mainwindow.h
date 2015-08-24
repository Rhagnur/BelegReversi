#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QMediaPlayer>
#include <QMediaPlaylist>
#include "controllerField.h"
#include "viewHS.h"
#include "ui_mainwindow.h"
#include "ui_gamewidget.h"
#include "ui_menuwidget.h"
#include "ui_pvpwidget.h"
#include "ui_hswidget.h"
#include "ui_optionwidget.h"
#include "mydict.h"


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

    //! Eventfilter
    /*!
     * \brief Needed for resize and Mouseclick event
     * \param target
     * \param event
     * \return bool
     */
    bool eventFilter(QObject *target, QEvent *event);

private slots:
    void on_pushButton_IngameBack_clicked();
    void on_pushButton_IngameSkip_clicked();
    void on_pushButton_StartPvP_clicked();
    void on_pushButton_optionsMenu_clicked();
    void on_pushButton_IngameOptions_clicked();
    void changeVolume(int value);
    void toggleVolume(bool checked);
    void changeDesign(int design);
    void on_pushButton_StartAI_clicked();
    void on_pushButton_StartGamePvP_clicked();
    void on_pushButton_Highscore_clicked();
    void on_pushButton_HSBack_clicked();
    void on_pushButton_BackPVP_clicked();
    void on_pushButton_HSExport_clicked();
    void on_pushButton_OptionBack_clicked();
    void on_pushButton_OptionMusikLoad_clicked();
    void on_comboBox_HSSotieren_activated(int index);
    void on_comboBox_OptionSprache_activated(int index);

private:
    QWidget *menuContainer = new QWidget();
    QWidget *gameContainer = new QWidget();
    QWidget *pvpContainer = new QWidget();
    QWidget *hsContainer = new QWidget();
    QWidget *optionContainer = new QWidget();
    Ui::MainWindow *mainUI;
    Ui::GameWidget *gameWidget;
    Ui::MenuWidget *menuWidget;
    Ui::PvPWidget *pvpWidget;
    Ui::HSWidget *hsWidget;
    Ui::OptionWidget *optionWidget;
    controllerField* controllField;
    bool menuIsInit = false, ingameOptionOn = false;
    QMediaPlayer *player;
    QMediaPlaylist *playList;
    ViewHS *hsField;
    int w = 500,h = 500, offset, design = 0;
    MyDict *dict;
    std::string *myDict;
    void changeLanguage();

};

#endif // MAINWINDOW_H
