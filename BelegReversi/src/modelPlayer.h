#ifndef MODELPLAYER_H
#define MODELPLAYER_H

#include <QString>

//! Player Model Class
/*!
 * \brief Definition of a player
 */
class modelPlayer
{
public:

    //! Constructor
    modelPlayer();

    /*!
     * \brief Sets the new playerName for a player
     * \param name
     */
    void setPlayerName(QString name);

    /*!
     * \brief Sets the new stoneCount for a player
     * \param count
     */
    void setPlayerStoneCount(int count);

    /*!
     * \brief Gets the current stoneCount from player
     * \return stoneCount
     */
    int getPlayerStoneCount();  

    /*!
     * \brief Gets the current playerName from player
     * \return playerName
     */
    QString getPlayerName();

private:

    int stoneCount;
    QString playerName;

};

#endif // MODELPLAYER_H
