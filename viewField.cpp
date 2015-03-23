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

void viewField::mousePressEvent(QGraphicsSceneMouseEvent *event)
{

    int x = event->scenePos().x();
    int y = event->scenePos().y();
    std::cout << "Mausklick erkannt" + std::to_string(x) + " x " + std::to_string(y) << std::endl;
    /*
    if (reversiField->evaluateClick(x, y))
    {
        std::cout << "Guter Zug" << std::endl;
        drawField();
    }
    else
    {
        std::cout << "Kein gueltiger Zug, nochmal" << std::endl;
        //kein gültiger Zug
    }
    */
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

    std::cout << "Zeichne Feld : " + std::to_string(x) + " x " + std::to_string(y) + " - " + std::to_string(width) + " x " + std::to_string(height) + " -  Value: " + std::to_string(value) << std::endl;
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
