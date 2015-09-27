#include "ai.h"

Ai::Ai()
{

}

std::vector<int> Ai::turn(modelField *field, int activePlayer, int otherPlayer)
{
    index = 0;
    modelField fieldIter = modelField(field->getFieldSize());
    this->activePlayer = activePlayer;  
    this->otherPlayer = otherPlayer;
    aiPlayer = activePlayer;
    humanPlayer = otherPlayer;
    std::vector<int> zug;

    for (int i = 0; i < field->getFieldSize(); i++)
    {
        for (int j = 0; j < field->getFieldSize(); j++)
        {
            fieldIter.setFieldValue(i, j, field->getFieldValue(i, j));
            if (field->getFieldValue(i, j) == 3) {
                zug.push_back(i);
                zug.push_back(j);
            }
        }
    }


    tree<NodeInfo>::iterator root, parent, firstChild;
    root = possTurnsTree.begin();
    NodeInfo rootInfos, firstChildInfo;
    std::vector<int> tempTurn;
    tempTurn.push_back(50);
    tempTurn.push_back(50);

    firstChildInfo.setDiffStoneCount(0);
    firstChildInfo.setTurn(tempTurn);
    firstChildInfo.setField(clearField(*field));

    parent = possTurnsTree.insert(root, rootInfos);
    firstChild = possTurnsTree.append_child(parent, firstChildInfo);

    treeIteratorVector.push_back(firstChild);

    while (index < tiefe)
    {
        processList();
        index += 1;
    }

    std::vector<int> bestTurn = findBestTurn();

    possTurnsTree.clear();
    treeIteratorVector.clear();
    firstChildrenVector.clear();
    return bestTurn;
}

std::vector<int> Ai::findBestTurn()
{
    tree<NodeInfo>::iterator tempIte, rootTemp;
    std::vector<int> subTreeWinChance;
    NodeInfo bestOutcome, rootTempInfo;
    int highestNumber = 0;
    int idex = 0;
    for (unsigned int i = 0; i < firstChildrenVector.size(); i++)
    {
        tree<NodeInfo>::iterator subTree = firstChildrenVector.at(i);
        tree<NodeInfo>::iterator beginSubTree = subTree.begin();
        if(beginSubTree!=subTree.end()) {
           tree<NodeInfo>::iterator sib2=subTree.begin();
           tree<NodeInfo>::iterator end2=subTree.end();
           std::vector<int>winChance;

              while(sib2!=end2) {
                  if (possTurnsTree.depth(sib2) == tiefe + 1)
                  {
                      NodeInfo temp = sib2.node->data;
                      if (temp.getDiffStoneCount() > 0)
                      {
                          std::cout << "Möglicher Sieg" << std::endl;
                          winChance.push_back(10);
                      }
                      else if (temp.getDiffStoneCount() == 0)
                      {
                          std::cout << "Mögliches Unentschieden" << std::endl;
                          winChance.push_back(0);
                      }
                      else
                      {
                          std::cout << "Mögliche Niederlage" << std::endl;
                          winChance.push_back(-10);
                      }
                  }
                ++sib2;
                }

              int tempErg = 0;
              for (unsigned int i = 0; i < winChance.size(); i++)
              {
                  tempErg += winChance.at(i);
              }

              subTreeWinChance.push_back(tempErg);

              }
    }
    //bestOutcome.getField()->showFieldDebug();
    //std::cout << "Höchste Punktzahl " + QString::number(bestOutcome.getDiffStoneCount()).toStdString() << std::endl;

    for (unsigned int i = 0; i < subTreeWinChance.size(); i++)
    {
        if (highestNumber < subTreeWinChance.at(i))
        {
            highestNumber = subTreeWinChance.at(i);
            idex = i;
        }
    }

    std::cout << "Höchst mögliche Punktzahl gefunden bei Subtree (i) :" + QString::number(idex).toStdString() + " Punktzahl = " + QString::number(highestNumber).toStdString() << std::endl;


    rootTemp = firstChildrenVector.at(idex);
    rootTempInfo = rootTemp.node->data;

    return rootTempInfo.getTurn();
}

void Ai::debugTree()
{
    tree<NodeInfo>::iterator begin = possTurnsTree.begin();

    if(begin!=possTurnsTree.end()) {
       std::cout << std::endl;
       tree<NodeInfo>::iterator sib2=possTurnsTree.begin(begin);
          tree<NodeInfo>::iterator end2=possTurnsTree.end(begin);
          while(sib2!=end2) {
            if (possTurnsTree.depth(sib2) == tiefe + 1)
            {
                std::cout << "Endleaf erreicht" << std::endl;

            }
            NodeInfo temp = sib2.node->data;
            for(int i=0; i<possTurnsTree.depth(sib2); ++i)
                std::cout << "#";
            std::cout << temp.getDiffStoneCount() << std::endl;
            temp.getField()->showFieldDebug();
            std::cout << std::endl;
            ++sib2;
            }
          }

}

void Ai::processList()
{

    std::cout << "processList() start" <<std::endl;
    std::vector<tree<NodeInfo>::iterator> tempVec;
    for (unsigned int i = 0; i < treeIteratorVector.size(); i++)
    {
        tempVec.push_back(treeIteratorVector.at(i));
    }

    treeIteratorVector.clear();



    for (unsigned int i = 0; i < tempVec.size(); i++)
    {
        tree<NodeInfo>::iterator temp;
        NodeInfo tempInf;
        temp = tempVec.at(i);
        tempInf = temp.node->data;
        append_children(searchPossibleTurns(*tempInf.getField()), temp);
    }
    changePlayer();
    std::cout << "processList() end" <<std::endl;
}

void Ai::append_children(modelField &field, tree<NodeInfo>::iterator parent)
{
    for (int i = 0; i < field.getFieldSize(); i++)
    {
        for (int j = 0; j < field.getFieldSize(); j++)
        {
            if (field.getFieldValue(i, j) == 3)
            {
                int offset = 0;
                if ((i == 0 && j == 0) || (i == 0 && j == field.getFieldSize() - 1) || (i == field.getFieldSize() -1 && j == 0) || (i == field.getFieldSize() -1 && j == field.getFieldSize() - 1))
                {
                    offset = 99;
                }

                tree<NodeInfo>::iterator temp;
                NodeInfo tempInfos;
                std::vector<int> tempTurn;
                modelField fieldCopy = modelField(field.getFieldSize());
                fieldCopy.copyField(field);
                fieldCopy.setFieldValue(i, j, activePlayer);
                fieldCopy = flipStones(i, j, fieldCopy);

                tempTurn.push_back(i);
                tempTurn.push_back(j);
                tempInfos.setDiffStoneCount(calculateStoneCountForTurn(fieldCopy) + offset);
                tempInfos.setField(clearField(fieldCopy));
                tempInfos.setTurn(tempTurn);

                temp = possTurnsTree.append_child(parent, tempInfos);

                treeIteratorVector.push_back(temp);
                if(index == 0)
                {
                    firstChildrenVector.push_back(temp);
                }
            }
        }
    }

}

modelField& Ai::clearField(modelField &field)
{
    for (int i = 0; i < field.getFieldSize(); i++)
    {
        for (int j = 0; j < field.getFieldSize(); j++)
        {
            if (field.getFieldValue(i, j) == 3)
            {
                field.setFieldValue(i, j , 0);
            }
        }
    }
    return field;
}

int Ai::calculateStoneCountForTurn(modelField &field)
{
    int aiCount = 0;
    int humanCount = 0;
    int ergebnis = 0;

    for (int i = 0; i < field.getFieldSize(); i++)
    {
        for (int j = 0; j < field.getFieldSize(); j++)
        {
            if (field.getFieldValue(i, j) == aiPlayer)
            {
                aiCount ++;
            }
            if (field.getFieldValue(i, j) == humanPlayer)
            {
                humanCount ++;
            }
        }
    }

    ergebnis = aiCount - humanCount;
    return ergebnis;
}

modelField &Ai::flipStones(int i, int j, modelField &field)
{
    //flip down
    if (i != field.getFieldSize() - 1 && field.getFieldValue(i + 1, j) == otherPlayer)
    {
        int iIterator = i + 1;
        while (iIterator < field.getFieldSize() - 1 && field.getFieldValue(iIterator, j) == otherPlayer)
        {
            iIterator++;
        }
        if (field.getFieldValue(iIterator, j) == activePlayer)
        {
            for (int y = i + 1; y < iIterator; y++)
            {
                field.setFieldValue(y, j, activePlayer);

            }
        }
    }
    //flip down-right
    if (i != field.getFieldSize() - 1 && j != field.getFieldSize() - 1 && field.getFieldValue(i + 1, j + 1) == otherPlayer)
    {
        int iIterator = i + 1;
        int jIterator = j + 1;
        while (iIterator < field.getFieldSize() - 1 && jIterator < field.getFieldSize() - 1 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator++;
            jIterator++;
        }
        if (field.getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i + 1;
            int x = j + 1;
            while (y < iIterator && x < jIterator)
            {
                field.setFieldValue(y, x, activePlayer);

                y++;
                x++;
            }
        }
    }
    //flip right
    if (i != field.getFieldSize() - 1 && j != field.getFieldSize() - 1 && field.getFieldValue(i, j + 1) == otherPlayer)
    {
        int jIterator = j + 1;
        while (jIterator < field.getFieldSize() - 1 && field.getFieldValue(i, jIterator) == otherPlayer)
        {
            jIterator++;
        }
        if (field.getFieldValue(i, jIterator) == activePlayer)
        {
            for (int x = j + 1; x < jIterator; x++)
            {
                field.setFieldValue(i, x, activePlayer);

            }
        }
    }
    //flip up-right
    if (i != 0 && j != field.getFieldSize() - 1 && field.getFieldValue(i - 1, j + 1) == otherPlayer)
    {
        int iIterator = i - 1;
        int jIterator = j + 1;
        while (iIterator > 0 && jIterator < field.getFieldSize() - 1 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator--;
            jIterator++;
        }
        if (field.getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i - 1;
            int x = j + 1;
            while (y > iIterator && x < jIterator)
            {
                field.setFieldValue(y, x, activePlayer);

                y--;
                x++;
            }
        }
    }
    //flip up
    if (i != 0 && field.getFieldValue(i - 1, j) == otherPlayer)
    {
        int iIterator = i - 1;
        while (iIterator > 0 && field.getFieldValue(iIterator, j) == otherPlayer)
        {
            iIterator--;
        }
        if (field.getFieldValue(iIterator, j) == activePlayer)
        {
            for (int y = i - 1; y > iIterator; y--)
            {
                field.setFieldValue(y, j, activePlayer);

            }
        }
    }
    //flip up-left
    if (i != 0 && j != 0 && field.getFieldValue(i - 1, j - 1) == otherPlayer)
    {
        int iIterator = i - 1;
        int jIterator = j - 1;
        while (iIterator > 0 && jIterator > 0 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator--;
            jIterator--;
        }
        if (field.getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i - 1;
            int x = j - 1;
            while (y > iIterator && x > jIterator)
            {
                field.setFieldValue(y, x, activePlayer);

                y--;
                x--;
            }
        }
    }
    //flip left
    if (j != 0 && field.getFieldValue(i, j - 1) == otherPlayer)
    {
        int jIterator = j - 1;
        while (jIterator > 0 && field.getFieldValue(i, jIterator) == otherPlayer)
        {
            jIterator--;
        }
        if (field.getFieldValue(i, jIterator) == activePlayer)
        {
            for (int x = j - 1; x > jIterator; x--)
            {
                field.setFieldValue(i, x, activePlayer);

            }
        }
    }
    //flip down-left
    if (i != field.getFieldSize() - 1 && j != 0 && field.getFieldValue(i + 1, j - 1) == otherPlayer)
    {
        int iIterator = i + 1;
        int jIterator = j - 1;
        while (iIterator < field.getFieldSize() - 1 && jIterator > 0 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
        {
            iIterator++;
            jIterator--;
        }
        if (field.getFieldValue(iIterator, jIterator) == activePlayer)
        {
            int y = i + 1;
            int x = j - 1;
            while (y < iIterator && x > jIterator)
            {
                field.setFieldValue(y, x, activePlayer);

                y++;
                x--;
            }
        }
    }

    return field;
}

bool Ai::isPossibleTurn(int i, int j, modelField &field)
{
            if (i != field.getFieldSize() - 1 && field.getFieldValue(i + 1, j) == otherPlayer)
            {
                int iIterator = i + 1;
                while (iIterator < field.getFieldSize() - 1 && field.getFieldValue(iIterator, j) == otherPlayer)
                {
                    iIterator++;
                }
                if (field.getFieldValue(iIterator, j) == activePlayer) return true;
            }
            if (i != field.getFieldSize() - 1 && j != field.getFieldSize() - 1 && field.getFieldValue(i + 1, j + 1) == otherPlayer)
            {
                int iIterator = i + 1;
                int jIterator = j + 1;
                while (iIterator < field.getFieldSize() - 1 && jIterator < field.getFieldSize() - 1 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator++;
                    jIterator++;
                }
                if (field.getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (i != field.getFieldSize() - 1 && j != field.getFieldSize() - 1 && field.getFieldValue(i, j + 1) == otherPlayer)
            {
                int jIterator = j + 1;
                while (jIterator < field.getFieldSize() - 1 && field.getFieldValue(i, jIterator) == otherPlayer)
                {
                    jIterator++;
                }
                if (field.getFieldValue(i, jIterator) == activePlayer) return true;
            }
            if (i != 0 && j != field.getFieldSize() - 1 && field.getFieldValue(i - 1, j + 1) == otherPlayer)
            {
                int iIterator = i - 1;
                int jIterator = j + 1;
                while (iIterator > 0 && jIterator < field.getFieldSize() - 1 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator--;
                    jIterator++;
                }
                if (field.getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (i != 0 && field.getFieldValue(i - 1, j) == otherPlayer)
            {
                int iIterator = i - 1;
                while (iIterator > 0 && field.getFieldValue(iIterator, j) == otherPlayer)
                {
                    iIterator--;
                }
                if (field.getFieldValue(iIterator, j) == activePlayer) return true;
            }
            if (i != 0 && j != 0 && field.getFieldValue(i - 1, j - 1) == otherPlayer)
            {
                int iIterator = i - 1;
                int jIterator = j - 1;
                while (iIterator > 0 && jIterator > 0 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator--;
                    jIterator--;
                }
                if (field.getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            if (j != 0 && field.getFieldValue(i, j - 1) == otherPlayer)
            {
                int jIterator = j - 1;
                while (jIterator > 0 && field.getFieldValue(i, jIterator) == otherPlayer)
                {
                     jIterator--;
                }
                if (field.getFieldValue(i, jIterator) == activePlayer) return true;
            }
            if (i != field.getFieldSize() - 1 && j != 0 && field.getFieldValue(i + 1, j - 1) == otherPlayer)
            {
                int iIterator = i + 1;
                int jIterator = j - 1;
                while (iIterator < field.getFieldSize() - 1 && jIterator > 0 && field.getFieldValue(iIterator, jIterator) == otherPlayer)
                {
                    iIterator++;
                    jIterator--;
                }
                if (field.getFieldValue(iIterator, jIterator) == activePlayer) return true;
            }
            return false;
}

modelField &Ai::searchPossibleTurns(modelField &field)
{

    for (int i = 0; i < field.getFieldSize(); i++)
    {
        for (int j = 0; j < field.getFieldSize(); j++)
        {
            // First, set all previous possible fields back to normal
            if (field.getFieldValue(i, j) == 3)
            {
                field.setFieldValue(i, j , 0);
            }
            // Now, check which fields are possible turns
            if (field.getFieldValue(i, j) == 0)
            {
                if (isPossibleTurn(i, j, field))
                {
                    field.setFieldValue(i, j, 3);
                }
            }
        }
    }
    return field;
}

void Ai::changePlayer()
{
    int temp = activePlayer;
    activePlayer = otherPlayer;
    otherPlayer = temp;
}
