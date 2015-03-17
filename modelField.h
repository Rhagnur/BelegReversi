#ifndef MODELFIELD_H
#define MODELFIELD_H

#include "modelElement.h"

class modelField
{
public:
    modelField(int fieldSize);
    void setFieldValue(int i, int j, int value);
    int getFieldValue(int i, int j);
    int getFieldSize();
    void showFieldDebug();

private:
    modelElement** field;
    int fieldSize;
};

#endif // MODELFIELD_H
