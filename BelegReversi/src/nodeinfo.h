#ifndef NODEINFO_H
#define NODEINFO_H

#include "modelField.h"
#include <vector>

/*!
 * \brief Definition of information node of the search tree
 */
class NodeInfo
{
public:
    /*!
     * \brief Constructor
     */
    NodeInfo();

    /*!
     * \brief setDiffStoneCount
     * \param diffCount
     */
    void setDiffStoneCount(int diffCount);

    /*!
     * \brief setField
     * \param field
     */
    void setField(modelField &field);

    /*!
     * \brief setTurn
     * \param turn
     */
    void setTurn(std::vector<int> turn);

    /*!
     * \brief setWhosTurn
     * \param playerID
     */
    void setWhosTurn(int playerID);

    /*!
     * \brief setWinChance
     * \param winChance
     */
    void setWinChance(int winChance);


    /*!
     * \brief getDiffStoneCount
     * \return int diffCount
     */
    int getDiffStoneCount();

    /*!
     * \brief getField
     * \return modelField field
     */
    modelField *getField();

    /*!
     * \brief getTurn
     * \return std::vector<int> turn
     */
    std::vector<int> getTurn();

    /*!
     * \brief getWhosTurn
     * \return
     */
    int getWhosTurn();

    /*!
     * \brief getWinChance
     * \return
     */
    int getWinChance();

private:
    int diffStoneCount = 0, whosTurn = 0, winChance = 0;
    std::vector<int> turn;
    modelField *field;
};

#endif // NODEINFO_H
