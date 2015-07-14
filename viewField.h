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
    QPixmap *empty = new QPixmap("C:\\Github\\BelegReversi\\img\\design1\\emptyField.png");
    QPixmap *player1 = new QPixmap("C:\\Github\\BelegReversi\\img\\design1\\greyStone.png");
    QPixmap *player2 = new QPixmap("C:\\Github\\BelegReversi\\img\\design1\\brownStone.png");
    QPixmap *possible = new QPixmap("C:\\Github\\BelegReversi\\img\\design1\\possibleTurn.png");



};

#endif // VIEWFIELD_H
