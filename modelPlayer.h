#ifndef MODELPLAYER_H
#define MODELPLAYER_H

#include <string>

class modelPlayer
{
public:
    modelPlayer(std::string name, int stones);
    int getPlayerStoneCount();
    void setPlayerStoneCount(int count);
    std::string getPlayerName();
    void setPlayerName(std::string name);

private:
    int stoneCount;
    std::string playerName;

};

#endif // MODELPLAYER_H
