#ifndef VIEWFIELD_H
#define VIEWFIELD_H

#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <string>
#include <QList>


class viewField : public QGraphicsScene
{
    Q_OBJECT
public:
    viewField();
    void drawElement(int x, int y, int width, int height, int value, int design, bool showPossTurns);
    void drawText(std::string text);
    viewField* getViewField();
    void clearField();


private:
    QGraphicsPixmapItem *field;
    QList<QGraphicsPixmapItem> *list;

};

#endif // VIEWFIELD_H
