#include "modelElement.h"

modelElement::modelElement()
{
    elementValue = 0;
}

void modelElement::setValue(int value)
{
    elementValue = value;
}

int modelElement::getValue()
{
    return elementValue;
}
