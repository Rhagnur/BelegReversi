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
    void drawField(int x, int y, int width, int height, int value);
    viewField* getViewField();


private:
    QGraphicsPixmapItem *field0, *field1, *field2, *field3;
    QPixmap *empty = new QPixmap("c:\\emptyField.png");
    QPixmap *player1 = new QPixmap("c:\\greyStone.png");
    QPixmap *player2 = new QPixmap("c:\\brownStone.png");
    QPixmap *possible = new QPixmap("c:\\possibleTurn.png");



};

#endif // VIEWFIELD_H
