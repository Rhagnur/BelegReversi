#ifndef MODELELEMENT_H
#define MODELELEMENT_H

class modelElement
{
public:
    modelElement();
    void setValue(int value);
    int getValue();

private:
    int elementValue;
};

#endif // MODELELEMENT_H
