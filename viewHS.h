#ifndef VIEWHS_H
#define VIEWHS_H

#include <QImage>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsItem>

#include <string>
#include <iostream>

//! Highscore View
/*!
 * \brief View for the Highscore
 * inherits from QGraphicsScene
 */
class ViewHS : public QGraphicsScene
{
public:
    //!Constructor
    ViewHS();

    //! Clear method
    /*!
     * \brief Clears the complete Highscore Scene
     */
    void clearField();

    //! Draw method
    /*!
     * \brief draws piece of text for highscore output
     * \param text
     * complete highscore query as string
     */
    void drawText(std::string text);

    //! Get method
    /*!
     * \brief getViewField
     * \return ViewHS object
     */
    ViewHS* getViewField();

};

#endif // VIEWHS_H
