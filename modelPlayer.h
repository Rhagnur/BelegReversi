#ifndef MODELPLAYER_H
#define MODELPLAYER_H

#include <string>

//! Player Model Class
/*!
 * \brief The player model class
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
    void setPlayerName(std::string name);

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
    std::string getPlayerName();

private:

    int stoneCount;
    std::string playerName;

};

#endif // MODELPLAYER_H
