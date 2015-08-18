#ifndef MENU_H
#define MENU_H

#include <iostream>
#include <QGraphicsScene>
#include <QSlider>
#include <QLabel>
#include <QCheckBox>

class menu: public QGraphicsScene
{
public:
    menu();
    void addOptionElements();
    QSlider *volSlider, *designSlider;
    QCheckBox *volOnOff;

private:
    QLabel *vol1Label;
    QLabel *vol2Label;
    QLabel *designLabel;
    QLabel *placeholder2Label;


    int volumeLevel;
};

#endif // MENU_H
