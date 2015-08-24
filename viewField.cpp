#include "viewField.h"

viewField::viewField()
{
    pixmapItemList = new QList<QGraphicsPixmapItem*>();
    pixmapList = new QList<QPixmap*>();
}

viewField::~viewField()
{
    delete pixmapItemList;
    delete pixmapList;
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
    QFont font;
    QGraphicsTextItem * textitem = new QGraphicsTextItem;
    QString textString = "<p style='text-align: center;'>" + QString::fromStdString(text) + "</p>";

    font.setPointSize(30);
    font.setBold(true);
    font.setFamily("Verdana");
    textitem->setTextWidth(this->width());
    textitem->setPos(0,100);
    textitem->setFont(font);
    textitem->setDefaultTextColor(Qt::white);
    textitem->setHtml(textString);

    this->addItem(textitem);
}

void viewField::drawElement(int x, int y, int width, int height, int value, int design, bool showPossTurns)
{
    QPixmap *empty, *player1, *player2, *possible;

    if (design == 0)
    {
        empty = new QPixmap(":/img/design1/emptyField.png");
        player1 = new QPixmap(":/img/design1/greyStone.png");
        player2 = new QPixmap(":/img/design1/brownStone.png");
        if (showPossTurns)
        {
            possible = new QPixmap(":/img/design1/possibleTurn.png");
        }
        else
        {
            possible = new QPixmap(":/img/design1/emptyField.png");
        }

    }
    if (design == 1)
    {
        empty = new QPixmap(":/img/design2/emptyField.png");
        player1 = new QPixmap(":/img/design2/whiteStone.png");
        player2 = new QPixmap(":/img/design2/blackStone.png");
        if (showPossTurns)
        {
            possible = new QPixmap(":/img/design2/possibleTurn.png");
        }
        else
        {
            possible = new QPixmap(":/img/design2/emptyField.png");
        }
    }
    if (design == 2)
    {
        empty = new QPixmap(":/img/design3/emptyField.png");
        player1 = new QPixmap(":/img/design3/greyStone.png");
        player2 = new QPixmap(":/img/design3/brownStone.png");
        if (showPossTurns)
        {
            possible = new QPixmap(":/img/design3/possibleTurn.png");
        }
        else
        {
            possible = new QPixmap(":/img/design3/emptyField.png");
        }
    }

    pixmapList->append(empty);
    pixmapList->append(player1);
    pixmapList->append(player2);
    pixmapList->append(possible);


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
    pixmapItemList->append(field);

}
