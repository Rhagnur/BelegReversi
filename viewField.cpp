#include "viewField.h"
#include <iostream>

viewField::viewField()
{
    this->setBackgroundBrush(Qt::yellow);
    testStringXY = "Keine Daten enthalten";
}

void viewField::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    int x = event->scenePos().x();
    int y = event->scenePos().y();

    std::cout << "Mausklick erkannt" <<std::endl;
    testStringXY = "X = " + std::to_string(x) + " und Y = " + std::to_string(y);
    testStringSize = "Groesse = " + std::to_string(this->width()) + " x " + std::to_string(this->height());
    QGraphicsEllipseItem* kreis = new QGraphicsEllipseItem(x-5, y-5, 10, 10);
    this->addItem(kreis);

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
}

std::string viewField::returnTestStringXY()
{
    return testStringXY;
}


void viewField::startReversi(int w, int h)
{
    reversiField = new controllerField(6);
    updateFieldSize(w, h);
    reversiField->startGame();
    drawField();
}

void viewField::updateFieldSize(int w, int h)
{
    if (w > h)
    {
        w = h;
    }
    else
    {
        h = w;
    }
    reversiField->setFieldSize(w, h);
}

void viewField::drawField()
{
    int size = reversiField->getGamingFieldMatrixSize();
    int fieldWidth = reversiField->getGamingFieldWidth();
    int fieldHeight = reversiField->getGamingFieldHeight();
    QBrush whiteBrush(Qt::white);   //empty
    QBrush blackBrush(Qt::black);   //palyer 2
    QBrush grayBrush(Qt::gray);     //player 1
    QBrush redBrush(Qt::red);       //possible turn
    QPen blackPen(Qt::black);
    blackPen.setWidth(0);

    this->clear();

    for (int j = 0; j < size; j++)
    {
        for (int i = 0; i < size; i++)
        {
            //Zeichne leeres Feld
            if ( reversiField->getGamingFieldElementValue(i, j) == 0 )
            {
                rectangle = this->addRect(j*(fieldWidth/size), i*(fieldHeight/size), fieldWidth/size, fieldHeight/size, blackPen, whiteBrush);
            }
            //Zeichne Spiele 1 Feld
            else if ( reversiField->getGamingFieldElementValue(i, j) == 1 )
            {
                rectangle = this->addRect(j*(fieldWidth/size), i*(fieldHeight/size), fieldWidth/size, fieldHeight/size, blackPen, grayBrush);
            }
            //Zeichne Spieler 2 Feld
            else if ( reversiField->getGamingFieldElementValue(i, j) == 2 )
            {
                rectangle = this->addRect(j*(fieldWidth/size), i*(fieldHeight/size), fieldWidth/size, fieldHeight/size, blackPen, blackBrush);
            }
            //Zeichen Möglicher Zug Feld
            else if ( reversiField->getGamingFieldElementValue(i, j) == 3 )
            {
                rectangle = this->addRect(j*(fieldWidth/size), i*(fieldHeight/size), fieldWidth/size, fieldHeight/size, blackPen, redBrush);
            }
        }
    }
}
