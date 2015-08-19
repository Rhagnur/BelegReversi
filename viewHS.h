#ifndef VIEWHS_H
#define VIEWHS_H
#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <string>

class ViewHS : public QGraphicsScene
{
public:
    ViewHS();
    void drawText(std::string text);
    ViewHS* getViewField();
    void clearField();
};

#endif // VIEWHS_H
