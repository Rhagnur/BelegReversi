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

    //! Set method
    /*!
     * \brief Sets the new height of the field
     * \param h
     */
    void setFieldHeight(int h);

    //! Set method
    /*!
     * \brief Sets the new width of the field
     * \param w
     */
    void setFieldWidth(int w);

    //! Set method
    /*!
     * \brief Sets the new value of one element of the field
     * \param i
     * \param j
     * \param value
     */
    void setFieldValue(int i, int j, int value);

    //! Get method
    /*!
     * \brief Gets the current height of the field
     * \return fieldHeight
     */
    int getFieldHeight();

    //! Get method
    /*!
     * \brief Gets the current width of the field
     * \return fieldWidth
     */
    int getFieldWidth();

    //! Get method
    /*!
     * \brief Gets the current size of the field
     * \return fieldSize
     */
    int getFieldSize();

    //! Get method
    /*!
     * \brief Gets the current value of one element of the field
     * \param i
     * \param j
     * \return value
     */
    int getFieldValue(int i, int j);

    //! Show Field in Console
    /*!
     * \brief Only for debug purpose
     */
    void showFieldDebug();

private:

    int** field = NULL, fieldSize, fieldWidth, fieldHeight;
};

#endif // MODELFIELD_H
