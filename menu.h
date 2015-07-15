#ifndef MENU_H
#define MENU_H

#include <QGraphicsScene>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

class menu: public QGraphicsScene
{
public:
    menu();
    void addOptionElements();

private:
    QLabel *vol1Label;
    QLabel *vol2Label;
    QLabel *placeholder1Label;
    QLabel *placeholder2Label;
    QSlider *volSlider;
    QCheckBox *volOnOff;


};

#endif // MENU_H
