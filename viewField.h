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
    viewField();
    void startReversi(int w, int h);
    void updateFieldSize(int w, int h);
    void drawField();


private:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    controllerField* reversiField;
    QGraphicsRectItem *rectangle;


};

#endif // VIEWFIELD_H
