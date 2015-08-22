#ifndef VIEWFIELD_H
#define VIEWFIELD_H

#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <string>


class viewField : public QGraphicsScene
{
public:
    viewField();
    void drawElement(int x, int y, int width, int height, int value, int design, bool showPossTurns);
    void drawText(std::string text);
    viewField* getViewField();
    void clearField();


private:
    QGraphicsPixmapItem *field;

};

#endif // VIEWFIELD_H
