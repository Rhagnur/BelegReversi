#ifndef MODELFIELD_H
#define MODELFIELD_H

#include <iostream>

//! Field Model Class
/*!
 * \brief The field model class
 */
class modelField
{
public:
    //! Constructor
    /*!
     * \brief Constructor
     * \param fieldSize
     * Size of the new gamingfield
     */
    modelField(int fieldSize);

    //! Deconstructor
    ~modelField();

    /*!
     * \brief Sets the new height of the field
     * \param h
     */
    void setFieldHeight(int h);

    /*!
     * \brief Sets the new width of the field
     * \param w
     */
    void setFieldWidth(int w);

    /*!
     * \brief Sets the new value of one element of the field
     * \param i
     * \param j
     * \param value
     */
    void setFieldValue(int i, int j, int value);

    /*!
     * \brief Gets the current height of the field
     * \return fieldHeight
     */
    int getFieldHeight();

    /*!
     * \brief Gets the current width of the field
     * \return fieldWidth
     */
    int getFieldWidth();

    /*!
     * \brief Gets the current size of the field
     * \return fieldSize
     */
    int getFieldSize();

    /*!
     * \brief Gets the current value of one element of the field
     * \param i
     * \param j
     * \return value
     */
    int getFieldValue(int i, int j);

    /*!
     * \brief Only for debug purpose
     */
    void showFieldDebug();

private:

    int** field = NULL, fieldSize, fieldWidth, fieldHeight;
};

#endif // MODELFIELD_H
