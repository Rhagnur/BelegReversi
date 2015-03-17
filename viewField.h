#ifndef VIEWFIELD_H
#define VIEWFIELD_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <string>
#include "controllerField.h"

class viewField : public QGraphicsScene
{
public:
    viewField(int w, int h);
    std::string returnTestStringXY();
    std::string returnTestStringSize();
    void startReversi();
    void updateFieldSize(int w, int h);
    void drawField();


private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    std::string testStringXY;
    std::string testStringSize;
    controllerField* reversiField;
    QGraphicsRectItem *rectangle;


};

#endif // VIEWFIELD_H
