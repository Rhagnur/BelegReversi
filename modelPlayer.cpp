#include "modelPlayer.h"

modelPlayer::modelPlayer()
{
}

//Start getter methods
int modelPlayer::getPlayerStoneCount()
{
    return stoneCount;
}

QString modelPlayer::getPlayerName()
{
    return playerName;
}

//Start setter methods
void modelPlayer::setPlayerStoneCount(int count)
{
    stoneCount = count;
}

void modelPlayer::setPlayerName(QString name)
{
    playerName = name;
}
