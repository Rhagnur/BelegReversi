#include "viewField.h"
#include <iostream>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>

viewField::viewField()
{

}

viewField* viewField::getViewField()
{
    return this;
}

void viewField::clearField()
{
    this->clear();
}

void viewField::drawText(std::string text)
{
    std::cout << text << std::endl;
    QFont f;
    f.setPointSize(40);
    f.setBold(true);
    f.setFamily("Verdana");
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setTextWidth(400);
    io->setPos(0,100);
    io->setFont(f);
    io->setPlainText(QString::fromStdString(text));
    io->setDefaultTextColor(Qt::white);

    this->addItem(io);
}

void viewField::drawElement(int x, int y, int width, int height, int value)
{
    QPixmap *empty = new QPixmap(":/img/design1/emptyField.png");
    QPixmap *player1 = new QPixmap(":/img/design1/greyStone.png");
    QPixmap *player2 = new QPixmap(":/img/design1/brownStone.png");
    QPixmap *possible = new QPixmap(":/img/design1/possibleTurn.png");

    if ( value == 0 )
    {
        *empty = empty->scaled(width, height);
        field = new QGraphicsPixmapItem();
        field->setPixmap(*empty);
    }

    else if ( value == 1 )
    {
        *player1 = player1->scaled(width, height);
        field = new QGraphicsPixmapItem();
        field->setPixmap(*player1);
    }
    else if ( value == 2 )
    {
        *player2 = player2->scaled(width, height);
        field = new QGraphicsPixmapItem();
        field->setPixmap(*player2);
    }
    else if ( value == 3 )
    {
        *possible = possible->scaled(width, height);
        field = new QGraphicsPixmapItem();
        field->setPixmap(*possible);
    }

    field->setPos(x, y);
    this->addItem(field);
}
