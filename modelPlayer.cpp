#include "modelPlayer.h"

modelPlayer::modelPlayer()
{
}

//Start getter methods
int modelPlayer::getPlayerStoneCount()
{
    return stoneCount;
}

std::string modelPlayer::getPlayerName()
{
    return playerName;
}

//Start setter methods
void modelPlayer::setPlayerStoneCount(int count)
{
    stoneCount = count;
}

void modelPlayer::setPlayerName(std::string name)
{
    playerName = name;
}
