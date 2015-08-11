#include "modelField.h"
#include <iostream>

modelField::modelField(int fieldSize)
{
    this->fieldSize = fieldSize;
    field = new int*[fieldSize];
    for (int i = 0; i < fieldSize; i++)
    {
        field[i] = new int[fieldSize];
        for (int j = 0; j < fieldSize; j++)
        {
            field[i][j] = 0;
        }
    }
}

void modelField::setFieldValue(int i, int j, int value)
{
    field[i][j] = value;
}

void modelField::setFieldWidth(int w)
{
    fieldWidth = w;
}

void modelField::setFieldHeight(int h)
{
    fieldHeight = h;
}

int modelField::getFieldValue(int i, int j)
{
    return field[i][j];
}

int modelField::getFieldSize()
{
    return fieldSize;
}

int modelField::getFieldWidth()
{
    return fieldWidth;
}

int modelField::getFieldHeight()
{
    return fieldHeight;
}

void modelField::showFieldDebug()
{
    for (int i = 0; i < fieldSize; i++)
    {
        for (int j = 0; j < fieldSize; j++)
        {
            std::cout << field[i][j];
        }
        std::cout<<std::endl;
    }
}
