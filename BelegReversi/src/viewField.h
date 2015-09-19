#ifndef VIEWFIELD_H
#define VIEWFIELD_H

#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>
#include <QGraphicsPixmapItem>
#include <QGraphicsTextItem>
#include <QTextBlockFormat>

#include <string>
#include <iostream>

//! Field View
/*!
 * \brief View for the Gamingfield
 * inherits from QGraphicsScene
 */
class viewField : public QGraphicsScene
{
public:
    //! Constructor
    viewField();

    //! Constructor
    ~viewField();

    /*!
     * \brief Clears the complete scene
     */
    void clearField();

    /*!
     * \brief Draws a single element from the field
     * \param x
     * starting x coord
     * \param y
     * starting y coord
     * \param width
     * \param height
     * \param value
     * value of the element, important for choosing the right image to drawn
     * \param design
     * important for choosing the right desing of the image
     * \param showPossTurns
     * if false then possibleMoves will be drawn as empty field
     */
    void drawElement(int x, int y, int width, int height, int value, int design, bool showPossTurns);

    /*!
     * \brief Draws the winning or draw text
     * \param text
     * text which should be shown in the scene
     */
    void drawText(QString text);

    /*!
     * \brief Gets the complete scene
     * \return viewField object
     */
    viewField* getViewField();

private:

    QGraphicsPixmapItem *field = NULL;
    QList<QGraphicsPixmapItem*> *pixmapItemList;
    QGraphicsTextItem *textitem = NULL;

};

#endif // VIEWFIELD_H
