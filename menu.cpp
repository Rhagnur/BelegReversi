#include "menu.h"

menu::menu()
{
    this->setBackgroundBrush(QBrush(Qt::lightGray, Qt::SolidPattern));
    vol1Label = new QLabel(QString::fromStdString("Volume regeln"));
    vol2Label = new QLabel(QString::fromStdString("Volume on-off"));
    placeholder1Label = new QLabel(QString::fromStdString("Platzhalter 1"));
    placeholder2Label = new QLabel(QString::fromStdString("Platzhalter 2"));;
    volSlider = new QSlider();
    volOnOff = new QCheckBox();
}

void menu::addOptionElements()
{
    vol1Label->setGeometry(40, 20, 100, 20);
    this->addWidget(vol1Label);

    volSlider->setGeometry(40, 50, 300, 20);
    volSlider->setOrientation(Qt::Horizontal);
    volSlider->setRange(0, 100);
    volSlider->setValue(100);
    this->addWidget(volSlider);

    vol2Label->setGeometry(40, 90, 100, 20);
    this->addWidget(vol2Label);

    volOnOff->setGeometry(40, 120, 20, 20);
    this->addWidget(volOnOff);
    volOnOff->setChecked(true);

    placeholder1Label->setGeometry(40, 160, 100, 20);
    this->addWidget(placeholder1Label);

    placeholder2Label->setGeometry(40, 230, 100, 20);
    this->addWidget(placeholder2Label);

}
