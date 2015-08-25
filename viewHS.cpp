#include "viewHS.h"

ViewHS::ViewHS()
{
    textitemList = new QList<QGraphicsTextItem*>();
}

ViewHS::~ViewHS()
{
    delete textitemList;
}

ViewHS* ViewHS::getViewField()
{
    return this;
}

void ViewHS::clearField()
{
    this->clear();
}

void ViewHS::drawText(std::string text)
{
    int i = 0, index = 0;
    std::string name = "";
    std::string score = "";
    std::string size = "";

    for (char test : text)
    {
        if(index == 0 && test != '#')
        {
            name += test;
        }
        if(index == 1 && test != '#')
        {
            score += test;
        }
        if(index == 2 && test != '#')
        {
            size += test;
        }

        if(test == '#')
        {
            index += 1;
        }
        if(test == '\n')
        {
            i += 1;
            index = 0;

            QFont f;
            f.setPointSize(16);
            f.setBold(true);
            f.setFamily("Verdana");
            QGraphicsTextItem * nameIO = new QGraphicsTextItem;
            QGraphicsTextItem * scoreIO = new QGraphicsTextItem;
            QGraphicsTextItem * sizeIO = new QGraphicsTextItem;

            nameIO->setPos(0,40 + (i * 35));
            nameIO->setFont(f);
            nameIO->setPlainText(QString::fromStdString(name));
            nameIO->setDefaultTextColor(Qt::white);
            this->addItem(nameIO);

            scoreIO->setPos(190,40 + (i * 35));
            scoreIO->setFont(f);
            scoreIO->setPlainText(QString::fromStdString(score));
            scoreIO->setDefaultTextColor(Qt::white);
            this->addItem(scoreIO);

            sizeIO->setPos(250,40 + (i * 35));
            sizeIO->setFont(f);
            sizeIO->setPlainText(QString::fromStdString(size));
            sizeIO->setDefaultTextColor(Qt::white);
            this->addItem(sizeIO);

            name = "";
            score = "";
            size = "";
            textitemList->append(nameIO);
            textitemList->append(scoreIO);
            textitemList->append(sizeIO);
        }
    }

}

