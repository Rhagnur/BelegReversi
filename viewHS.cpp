#include "viewHS.h"
#include <iostream>

ViewHS::ViewHS()
{

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
    std::cout << text << std::endl;
    QFont f;
    f.setPointSize(16);
    f.setBold(true);
    f.setFamily("Verdana");
    QGraphicsTextItem * io = new QGraphicsTextItem;
    io->setPos(0,100);
    io->setFont(f);
    io->setPlainText(QString::fromStdString(text));
    io->setDefaultTextColor(Qt::white);

    this->addItem(io);
}

