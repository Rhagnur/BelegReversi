#ifndef MODELFIELD_H
#define MODELFIELD_H

#include "modelElement.h"

class modelField
{
public:
    modelField(int fieldSize);
    void setFieldValue(int i, int j, int value);
    void setFieldWidth(int w);
    void setFieldHeight(int h);
    int getFieldValue(int i, int j);
    int getFieldSize();
    int getFieldWidth();
    int getFieldHeight();
    void showFieldDebug();

private:
    modelElement** field;
    int fieldSize;
    int fieldWidth;
    int fieldHeight;
};

#endif // MODELFIELD_H
