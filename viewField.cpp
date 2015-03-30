#include "viewField.h"
#include <iostream>
#include <QGraphicsPixmapItem>

viewField::viewField()
{

}

viewField* viewField::getViewField()
{
    return this;
}

void viewField::drawField(int x, int y, int width, int height, int value)
{


    //this->setBackgroundBrush(Qt::red);

    QGraphicsRectItem *rectangle;
    QBrush whiteBrush(Qt::white);   //empty
    QBrush blackBrush(Qt::black);   //player 2
    QBrush grayBrush(Qt::gray);     //player 1
    QBrush redBrush(Qt::red);       //possible turn
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);

    if ( value == 0 )
    {
        *empty = empty->scaled(width, height);
        field0 = new QGraphicsPixmapItem();
        field0->setPixmap(*empty);
        field0->setPos(x, y);
        this->addItem(field0);
    }

    else if ( value == 1 )
    {
        *player1 = player1->scaled(width, height);
        field1 = new QGraphicsPixmapItem();
        field1->setPixmap(*player1);
        field1->setPos(x, y);
        this->addItem(field1);
    }
    else if ( value == 2 )
    {
        *player2 = player2->scaled(width, height);
        field2 = new QGraphicsPixmapItem();
        field2->setPixmap(*player2);
        field2->setPos(x, y);
        this->addItem(field2);
    }
    else if ( value == 3 )
    {
        *possible = possible->scaled(width, height);
        field3 = new QGraphicsPixmapItem();
        field3->setPixmap(*possible);
        field3->setPos(x, y);
        this->addItem(field3);
    }
}
