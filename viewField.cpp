#include "viewField.h"
#include <iostream>

viewField::viewField()
{
    std::cout << "Scenesize = " + std::to_string(this->width()) + " x " + std::to_string(this->height());
}

viewField* viewField::getViewField()
{
    return this;
}

void viewField::drawField(int x, int y, int width, int height, int value)
{
    QGraphicsRectItem *rectangle;
    QBrush whiteBrush(Qt::white);   //empty
    QBrush blackBrush(Qt::black);   //player 2
    QBrush grayBrush(Qt::gray);     //player 1
    QBrush redBrush(Qt::red);       //possible turn
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);

    //Zeichne leeres Feld
    if ( value == 0 )
    {
        rectangle = this->addRect(x, y, width, height, blackPen, whiteBrush);
    }
    //Zeichne Spiele 1 Feld
    else if ( value == 1 )
    {
        rectangle = this->addRect(x, y, width, height, blackPen, grayBrush);
    }
    //Zeichne Spieler 2 Feld
    else if ( value == 2 )
    {
        rectangle = this->addRect(x, y, width, height, blackPen, blackBrush);
    }
    //Zeichen Möglicher Zug Feld
    else if ( value == 3 )
    {
        rectangle = this->addRect(x, y, width, height, blackPen, redBrush);
    }
}
