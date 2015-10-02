#include "nodeinfo.h"

NodeInfo::NodeInfo()
{
}

void NodeInfo::setDiffStoneCount(int diffCount)
{
    diffStoneCount = diffCount;
}

void NodeInfo::setField(modelField &field)
{
    this->field = new modelField(field.getFieldSize());
    this->field->copyField(field);
}

void NodeInfo::setTurn(std::vector<int> turn)
{
    this->turn = turn;
}

void NodeInfo::setWhosTurn(int playerID)
{
    this->whosTurn = playerID;
}

void NodeInfo::setWinChance(int winChance)
{
    this->winChance = winChance;
}

int NodeInfo::getDiffStoneCount()
{
    return diffStoneCount;
}

modelField* NodeInfo::getField()
{
    return field;
}

std::vector<int> NodeInfo::getTurn()
{
    return turn;
}

int NodeInfo::getWhosTurn()
{
    return whosTurn;
}

int NodeInfo::getWinChance()
{
    return winChance;
}
