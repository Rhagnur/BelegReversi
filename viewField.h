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
    void drawElement(int x, int y, int width, int height, int value);
    void drawText(std::string text);
    viewField* getViewField();
    void clearField();


private:
    QGraphicsPixmapItem *field;
    QPixmap *empty = new QPixmap(":/design1/emptyField.png");
    QPixmap *player1 = new QPixmap(":/design1/greyStone.png");
    QPixmap *player2 = new QPixmap(":/design1/brownStone.png");
    QPixmap *possible = new QPixmap(":/design1/possibleTurn.png");

};

#endif // VIEWFIELD_H
