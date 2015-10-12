#include "ai.h"

Ai::Ai()
{

}

Ai::~Ai()
{

}

std::vector<int> Ai::turn(modelField *field, int activePlayer, int otherPlayer, QString difficulty)
{

    if (difficulty == "easy") {
        modelField fieldIter = modelField(field->getFieldSize());
        std::vector<std::vector<int>> zugVector;

        for (int i = 0; i < field->getFieldSize(); i++)
                {
                    for (int j = 0; j < field->getFieldSize(); j++)
                    {
                        fieldIter.setFieldValue(i, j, field->getFieldValue(i, j));
                        if (field->getFieldValue(i, j) == 3) {
                            std::vector<int> zugTemp;
                            zugTemp.push_back(i);
                            zugTemp.push_back(j);
                            zugVector.push_back(zugTemp);
                        }
                    }
                }

        int randomNumber = rand() % zugVector.size();

        return zugVector.at(randomNumber);

    }
    else {

        if (difficulty == "normal") {
            tiefe = 3;
        }
        //Mehr Tiefe wäre besser, dann dauert aber die Bearbeitung des Baums länger
        if (difficulty == "hard") {
            tiefe = 5;
        }

        index = 0;
        modelField fieldIter = modelField(field->getFieldSize());
        this->activePlayer = activePlayer;
        this->otherPlayer = otherPlayer;
        aiPlayer = activePlayer;
        humanPlayer = otherPlayer;
        std::vector<int> zug;

        if (difficulty == "hard" && fieldIter.getFieldValue(0, 0) == 3) {
            std::vector<int> temp;
            temp.push_back(0);
            temp.push_back(0);

            return temp;
        }
        if (difficulty == "hard" && fieldIter.getFieldValue(0, fieldIter.getFieldSize() - 1) == 3) {
            std::vector<int> temp;
            temp.push_back(0);
            temp.push_back(fieldIter.getFieldSize() - 1);

            return temp;
        }
        if (difficulty == "hard" && fieldIter.getFieldValue(fieldIter.getFieldSize() - 1, 0) == 3) {
            std::vector<int> temp;
            temp.push_back(fieldIter.getFieldSize() - 1);
            temp.push_back(0);
            return temp;
        }
        if (difficulty == "hard" && fieldIter.getFieldValue(fieldIter.getFieldSize() - 1, fieldIter.getFieldSize() - 1) == 3) {
            std::vector<int> temp;
            temp.push_back(fieldIter.getFieldSize() - 1);
            temp.push_back(fieldIter.getFieldSize() - 1);
            return temp;
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




        for (unsigned int i = 0; i < firstChildrenVector.size(); i++) {
            calcWinChance(firstChildrenVector.at(i));
        }

        //debugTree();

        //std::cout << "#########################" << std::endl;

        //for (unsigned int i = 0; i < firstChildrenVector.size(); i++) {
        //    tree<NodeInfo>::iterator temp = firstChildrenVector.at(i);
        //    NodeInfo tempInf = temp.node->data;
        //    tempInf.getField()->showFieldDebug();
        //    std::cout << "WinChance : " + QString::number(tempInf.getWinChance()).toStdString() << std::endl;
        //}

        std::vector<int> bestTurn = findBestTurn();


        possTurnsTree.clear();
        treeIteratorVector.clear();
        firstChildrenVector.clear();
        return bestTurn;

    }

}

void Ai::calcWinChance(tree<NodeInfo>::iterator subtree)
{
    tree<NodeInfo>::iterator temp = subtree;
    while (temp != NULL) {
        if (temp.begin() == NULL) {
            if (temp.node->data.getDiffStoneCount() > 0) {
                temp.node->data.setWinChance(1);
            }
            else if (temp.node->data.getDiffStoneCount() == 0) {
                temp.node->data.setWinChance(0);
            }
            else {
                temp.node->data.setWinChance(-1);
            }
        }
        else {
            calcWinChance(temp.begin());
            int erg = 0;

            if (temp.node->data.getWhosTurn() == humanPlayer) {
                erg = 10;
                tree<NodeInfo>::iterator tempEndLeaf = temp.begin();
                while (tempEndLeaf != NULL) {
                    if (tempEndLeaf.node->data.getWinChance() < erg) {
                        erg = tempEndLeaf.node->data.getWinChance();
                    }
                    tempEndLeaf = tempEndLeaf.node->next_sibling;
                }
            }
            else {
                erg = -10;
                tree<NodeInfo>::iterator tempEndLeaf = temp.begin();
                while (tempEndLeaf != NULL) {
                    if (tempEndLeaf.node->data.getWinChance() > erg) {
                        erg = tempEndLeaf.node->data.getWinChance();
                    }
                    tempEndLeaf = tempEndLeaf.node->next_sibling;
                }
            }

            //std::cout << "Ergebnis: " + QString::number(erg).toStdString() << std::endl;
            temp.node->data.setWinChance(erg);
        }
        //temp.node->data.getField()->showFieldDebug();
        temp = temp.node->next_sibling;
    }
}

std::vector<int> Ai::findBestTurn()
{
    int winChance = -10, erg = 0;
    for (unsigned int i = 0; i < firstChildrenVector.size(); i++)
    {
        tree<NodeInfo>::iterator temp = firstChildrenVector.at(i);
        NodeInfo tempInf = temp.node->data;
        if (tempInf.getWinChance() > erg) {
            winChance = tempInf.getWinChance();
            erg = i;
        }
    }

    return firstChildrenVector.at(erg).node->data.getTurn();
}

void Ai::debugTree()
{
    std::cout << "debugTree()..." << std::endl;
    tree<NodeInfo>::iterator begin = possTurnsTree.begin();

    if(begin!=possTurnsTree.end()) {
       std::cout << std::endl;
       tree<NodeInfo>::iterator sib2=possTurnsTree.begin(begin);
          tree<NodeInfo>::iterator end2=possTurnsTree.end(begin);
          while(sib2!=end2) {
            if (possTurnsTree.depth(sib2) == tiefe + 1 || sib2.number_of_children() == 0)
            {
                std::cout << "Endleaf erreicht" << std::endl;
                NodeInfo temp = sib2.node->data;
                std::cout << "Diff : " + QString::number(temp.getDiffStoneCount()).toStdString() << std::endl;
                std::cout << "Chance : " + QString::number(temp.getWinChance()).toStdString() << std::endl;
                std::cout << "WhosTurn : " + QString::number(temp.getWhosTurn()).toStdString() << std::endl;
                temp.getField()->showFieldDebug();
                std::cout << std::endl;

            }



            ++sib2;

            /*for(int i=0; i<possTurnsTree.depth(sib2); ++i)
                std::cout << "#";*/

            }
            std::cout << std::endl;

          }

}

void Ai::processList()
{
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
}

void Ai::append_children(modelField &field, tree<NodeInfo>::iterator parent)
{
    for (int i = 0; i < field.getFieldSize(); i++)
    {
        for (int j = 0; j < field.getFieldSize(); j++)
        {
            if (field.getFieldValue(i, j) == 3)
            {
                tree<NodeInfo>::iterator temp;
                NodeInfo tempInfos;
                std::vector<int> tempTurn;
                modelField fieldCopy = modelField(field.getFieldSize());
                fieldCopy.copyField(field);
                fieldCopy.setFieldValue(i, j, activePlayer);
                fieldCopy = flipStones(i, j, fieldCopy);

                tempTurn.push_back(i);
                tempTurn.push_back(j);
                tempInfos.setDiffStoneCount(calculateStoneCountForTurn(fieldCopy));
                tempInfos.setField(clearField(fieldCopy));
                tempInfos.setTurn(tempTurn);
                tempInfos.setWhosTurn(activePlayer);

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
