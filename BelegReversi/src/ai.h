#ifndef AI_H
#define AI_H

#include "modelField.h"
#include "modelPlayer.h"
#include "nodeinfo.h"
#include "tree.hh"
#include <list>
#include <vector>

class Ai
{
public:
    Ai();
    std::vector<int> turn(modelField *field, int activePlayer, int otherPlayer);
private:

    modelField& flipStones(int i, int j, modelField &field);

    void processList();
    void append_children(modelField &field, tree<NodeInfo>::iterator parent);
    void debugTree();
    bool isPossibleTurn(int i, int j, modelField &field);
    modelField& searchPossibleTurns(modelField &field);
    modelField& clearField(modelField &field);
    int calculateStoneCountForTurn(modelField &field);
    void changePlayer();
    std::vector<int> findBestTurn();

    int activePlayer, otherPlayer, aiPlayer, humanPlayer;
    int tiefe = 5, index;

    tree<NodeInfo> possTurnsTree;
    std::vector<tree<NodeInfo>::iterator> treeIteratorVector;
    std::vector<tree<NodeInfo>::iterator> firstChildrenVector;
};

#endif // AI_H
