#ifndef NODEINFO_H
#define NODEINFO_H

#include "modelField.h"
#include <vector>


class NodeInfo
{
public:
    NodeInfo();

    void setDiffStoneCount(int diffCount);
    void setField(modelField &field);
    void setTurn(std::vector<int> turn);

    int getDiffStoneCount();
    modelField *getField();
    std::vector<int> getTurn();

private:
    int diffStoneCount;
    std::vector<int> turn;
    modelField *field;
};

#endif // NODEINFO_H
