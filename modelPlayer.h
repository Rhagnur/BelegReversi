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

    //! Set method
    /*!
     * \brief Sets the new playerName for a player
     * \param name
     */
    void setPlayerName(std::string name);

    //! Set method
    /*!
     * \brief Sets the new stoneCount for a player
     * \param count
     */
    void setPlayerStoneCount(int count);

    //! Get method
    /*!
     * \brief Gets the current stoneCount from player
     * \return stoneCount
     */
    int getPlayerStoneCount();  

    //! Get method
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
