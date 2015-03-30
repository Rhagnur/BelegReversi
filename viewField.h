#ifndef VIEWFIELD_H
#define VIEWFIELD_H

#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <string>


class viewField : public QGraphicsScene
{
public:
    viewField();
    void drawField(int x, int y, int width, int height, int value);
    viewField* getViewField();
    void mousePressEvent(QGraphicsSceneMouseEvent *event);


private:



};

#endif // VIEWFIELD_H
